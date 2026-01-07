#include "argo.h"

// INPUT JSON EXAMPLE:
// --------------------------------------
// {"x":10,"y":{"z":"hello"}}
// --------------------------------------

// PARSED JSON AST:
// --------------------------------------
// MAP
//  ├── key="x" → INTEGER(10)
//  └── key="y" → MAP
//         └── key="z" → STRING("hello")
// --------------------------------------


// TASK:
// - Read >>one<< JSON value from 'stream'.
// - That value can be:
//		- a NUMBER (int)
//		- a STRING
//		- a MAP (object)
// - Build the corresponding json struct tree into *dst.
// - Return 1 SUCCESS / Return -1 FAILURE.
// - On unexpected token:
//		- Print: "unexpected token %c\n"
// - On unexpected EOF:
//		- Print: "unexpected end of input"
//	WHITESPACE OUTSIDE OF A STRING == INVALID TOKEN.

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

// Prints error based on next character or EOF
void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

// Checks and consumes char 'c'
int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

// Must be char 'c' or throws error
int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

void	free_json(json j)
{
	switch (j.type)
	{
		case MAP:
			for (size_t i = 0; i < j.map.size; i++)
			{
				free(j.map.data[i].key);
				free_json(j.map.data[i].value);
			}
			free(j.map.data);
			break ;
		case STRING:
			free(j.string);
			break ;
		default:
			break ;
	}
}

void	serialize(json j)
{
	switch (j.type)
	{
		case INTEGER:
			printf("%d", j.integer);
			break ;
		case STRING:
			putchar('"');
			for (int i = 0; j.string[i]; i++)
			{
				if (j.string[i] == '\\' || j.string[i] == '"')
					putchar('\\');
				putchar(j.string[i]);
			}
			putchar('"');
			break ;
		case MAP:
			putchar('{');
			for (size_t i = 0; i < j.map.size; i++)
			{
				if (i != 0)
					putchar(',');
				serialize((json){.type = STRING, .string = j.map.data[i].key});
				putchar(':');
				serialize(j.map.data[i].value);
			}
			putchar('}');
			break ;
	}
}


// parse_map() - Parse a JSON MAP value: {"key":value, ...}
// Flow:
// 1. Must start with a '{'
// 2. Either: 
//		- Immediately see '}' -> Empty map.
//		- OR parse one or more "key":value pairs:
//			a) Parse key as a STRING (using parse_string())
//			b) Expect ':' between key and valye
//			c) Parse value with parse_value()
//			d) Store (key, value) in a groable array of pairs
//			e) After each pair:
//				- If ',' - then continue with next pair
//				- if '}' - then map is finished
//				- Anything else -> error.
// 3. On success:
//		- out->type = MAP
//		- out->map.data =allocated array of pairs
//		- out.map.size = number of pairs
// 4. On failure:
// 		- Print error (via expect() / unexpected())
//		- Free any partially built map
//		- Return 0
int	parse_map(json *out, FILE *stream)
{
	// Expect opening '{'
	if (!expect(stream, '{'))
		return (0);
	
	pair	*data = NULL;	// Dynamic array of key/value pairs
	size_t	size = 0;		// Number of pairs stored
	size_t	cap = 0;		// Current capacty of 'data' array

	// Check for empty map
	if (accept(stream, '}'))
	{
		out->type = MAP;
		out->map.data = NULL;
		out->map.size = 0;
		return (1);
	}

	// Parse one or more "key":value pairs
	while (1)
	{
		// Parse KEY as a string "key"
		char *key = NULL;
		if (!parse_string(&key, stream))
			goto error;
		
		// Expect ':' after the key
		if (!expect(stream, ':'))
		{
			free(key);
			goto error;
		}

		// Parse VALUE (number / string / map)
		json value;
		if (!parse_value(&value, stream))
		{
			free(key);
			goto error;
		}

		// Grow the array if needed
		if (size == cap)
		{
			size_t new_cap;
			if (cap == 0 )
				new_cap = 4;
			else
				new_cap = cap * 2;
			pair *tmp = realloc(data, new_cap * sizeof(pair));
			if (!tmp)
			{
				free(key);
				free_json(value);
				goto error;
			}
			data = tmp;
			cap = new_cap;
		}

		// Store (key, value) in the array
		data[size].key = key;
		data[size].value = value;
		size++;

		// After a pair, we MUST see either ',' (more pairs coming) OR '}' (end of map)
		if (accept(stream, ','))
		{
			// Loop again to parse the next pair
			continue ;
		}
		else if (accept(stream, '}'))
		{
			// End of map
			break ;
		}
		else
		{
			// Invalid char
			unexpected(stream);
			goto error;
		}
	}

	// Success -> fill out '*out' json.
	out->type = MAP;
	out->map.data = data;
	out->map.size = size;
	return (1);

error:
	for (size_t i = 0; i < size; i++)
	{
		free(data[i].key);
		free_json(data[i].value);
	}
	free(data);
	return (0);
}

// parse_integer() - Parse a JSON NUMBER value: 123 or -456
// Flow:
// 1. Look at the next char:
//		- Optional '-' sign
//		- Then one or more digits (0-9)
// 2. Build the integer value digit by digit
// 3. Store the final value in *out
// 4. Return 1 on success, 0 on failure
// NOTE:
//	 - No spaces allowed
//	 - If the first non-sign char is NOT a digit -> error.
int	parse_integer(int *out, FILE *stream)
{
	int	c;
	int	sign = 1;
	int	value = 0;

	// Check optional '-' sign
	c = peek(stream);
	if (c == '-')
	{
		getc(stream);		// Consume '-' char
		sign = -1;			// Set sign to negative
		c = peek(stream);	// Peek the next char
	}

	// Check that char is a DIGIT, if not -> error.
	if (!isdigit(c))
	{
		unexpected(stream);
		return (0);
	}

	// Consume digits and build the number
	while (isdigit(peek(stream)))
	{
		c = getc(stream);
		value = value * 10 + (c - '0');
	}

	// Apply sign and store result
	*out = (int)(sign * value);
	return (1);
}


// parse_string() - Parse a JSON STRING value: "...."
// Flow:
// 1. Must start with a double quote char
// 2. Build the value string char by char
//		- First validate the char
//		- Then append it to the growable buffer.
// 3. Handle escape sequences:
//		- \" => literal "
//		- \\ => literal '\' 
//		- Any other escape is invalid.
// 4. Stop when closing " quote is found.
// 5. Return 1 on success, 0 on failure.
// NOTE:
//	- Spaces allowed inside strings.
//	- EOF before closing quote is an error.
int	parse_string(char **out, FILE *stream)
{
	// Expect and consume the opening quote
	if (!expect(stream, '"'))
		return (0);
	
	// Create a small buffer where the extracted string will be built.
	// Grow as needed.
	size_t cap = 16;	// Initial buffer size
	size_t len = 0;		// Number of chars appended to buf
	char *buf = malloc(cap);
	if (!buf)
		return (0);

	while (1)
	{
		// getc() returns the current char and advances the pointer.
		int c = getc(stream);

		// Check unexpected EOF
		if (c == EOF)
		{
			free(buf);
			unexpected(stream); // Prints "unexpected EOF"
			return (0);
		}

		// Check if closing quote (end of string == break from build loop)
		if (c == '"')
			break ;
		
		// Check and handle escape sequence
		if (c == '\\')
		{
			// get the char after the escape char
			int esc = getc(stream);

			// Check unexpected EOF
			if (esc == EOF)
			{
				free(buf);
				unexpected(stream);
				return (0);
			}

			// Check if valid esc char " or '\'
			if (esc != '"' && esc != '\\')
			{
				// Push char back so unexpected() can print it
				ungetc(esc, stream);
				free(buf);
				unexpected(stream);
				return (0);
			}

			// Replace c (currently backslash) to the escaped char.
			c = esc;
		}

		// Grow the buffer if needed
		if (len + 1 >= cap)
		{
			cap *= 2;
			// Resize the block of memory pointed to by buf.
			char *tmp = realloc(buf, cap);
			if (!tmp)
			{
				free(buf);
				return (0);
			}
			buf = tmp;
		}

		// Store the validated character
		buf[len++] = (char)c;
	}

	// Null terminate the final value string
	buf[len] = '\0';
	*out = buf;
	return (1);
}

// parse_value() - Looks at the next character and decides what kind of JSON will be parsed.
// Flow:
// 1. Peek the next character (do not consume it).
// 2. Decide what kind of JSON value we are parsing:
//  	- If c == ", parse a STRING
// 		- If c == {, parse a MAP
// 		- If c == - OR digit, parse an INT.
//		- Anything else == Invalid token.
// 3. Fill the 'json' struct pointed to by *out accordingly.
// 4. Return 1 on success, 0 on failure.
int	parse_value(json *out, FILE *stream)
{
	// Look at the next char without consuming.
	int c = peek(stream);

	// If c == EOF, no value is present, error.
	if (c == EOF)
	{
		unexpected(stream);
		return (0);
	}

	// CASE 1: STRING value -> starts with "
	if (c == '"')
	{
		// String var to store the parsed string value;
		char *s = NULL;

		// parse_string() will:
		//	- consume the starting and ending quotes
		//	- handle \ and \\ escape sequences
		//	- allocate and fill a C string
		if (!parse_string(&s, stream))
			return (0);

		out->type = STRING;
		out->string = s;
		return (1);
	}

	// CASE 2: MAP value -> starts with {
	if (c == '{')
	{
		// parse_map() will:
		//	- consume '{'
		//  - parse zero or more "key":value pairs
		//  - consume the closing '}'
		//	- allocate an array of pair {key, value}
		if (!parse_map(out, stream))
			return (0);
		return (1);
	}

	// Case 3: INTEGER value -> starts with '-' or a digit.
	if (c == '-' || isdigit(c))
	{
		// Int var to store the parsed int value;
		int n;

		// parse_integer() will:
		//  - consume an optional '-'
		//  - consume one or more digits
		//  - store the result in 'n'
		if (!parse_integer(&n, stream))
			return (0);

		out->type = INTEGER;
		out->integer = n;
		return (1);
	}

	// Case 4: Anything else == invalid token.
	unexpected(stream);
	return (0);
}

// argo() - Parses *stream into a json struct.
// Flow;
// 1. Call a helper that parses a single JSON value from the current position:
//		- parse_value(json *out, FILE *stream);
// 2. If that fails:
//		- Print error and return -1
// 3. If it succeeds:
//		- Make sure we are at EOF.
//			- If there are extra characters after the valid value == error.
// 4. If everything is good:
//  	- Store the parsed result into *dst
//		- Return 1.
// NOTE: We also want to protect *dst so that free_json(*dst) is always safe.
int	argo(json *dst, FILE *stream)
{
	// Initialize dst to a safe value (so free_json() is valid)
	dst->type = INTEGER;
	dst->integer = 0;

	// Parse into temp file first
	json tmp;

	// Parse one JSON value from the stream
	if (!parse_value(&tmp, stream))
	{
		// parse_value already printed error (no need to do it here)
		// main calls free_json()
		return (-1);
	}

	// After a valid parse, there should be nothing left in the stream.
	// Stream should point to EOF.
	if (peek(stream) != EOF)
	{
		unexpected(stream); // Prints error message for unexptected token
		free_json(tmp);		// Free the tmp json that was built
		return (-1);
	}
	
	// On success: move the tmp to *dst.
	*dst = tmp;
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");
	json	file;
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}
	serialize(file);
	printf("\n");
}