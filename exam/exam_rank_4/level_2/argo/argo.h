#ifndef ARGO_H
# define ARGO_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


typedef struct	json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;


// Provided
int		peek(FILE *stream);
void	unexpected(FILE *stream);
int		accept(FILE *stream, char c);
int		expect(FILE *stream, char c);
void	free_json(json j);
void	serialize(json j);

// Not provided
int	parse_map(json *out, FILE *stream);
int	parse_integer(int *out, FILE *stream);
int	parse_string(char **out, FILE *stream);
int	parse_value(json *out, FILE *stream);
int	argo(json *dst, FILE *stream);


#endif