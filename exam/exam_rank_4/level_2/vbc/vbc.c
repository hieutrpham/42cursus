#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "vbc.h"

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c) // FIX: This was a single =, maybe its intentionally provided that way?
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

// FACTOR = Single number (like 3) OR something inside parenthesis (1+2).
// TERM = One or more factors, "glued" together with '*'.
// EXPR = One or more terms, "glued" together with '+'.

// This function parses a FACTOR
// 		FACTOR = Single digit number (0-9) OR a full expression inside parentheses (1+2)
//
// Logic:
//	- If the current character is a digit:
//		- Create a VAL node and consume the digit.
//	- Else if the current character is a '('
//		- Consume '('
//		- Parse an EXPR inside it
//		- expect and consume ')'
//	- Else
//		- Not a valid FACTOR, report unexpted token.
node *parse_factor(char **s)
{
	// Case 1: A digit -> VAL node.
	if (isdigit((unsigned char)**s))
	{
		node n;

		// Build a simple value node (leaf)
		n.type = VAL;
		n.val = **s - '0'; // Convert digit char to int.
		n.l = NULL;
		n.r = NULL;

		(*s)++;	// Consume the digit (advance the input pointer)
		return (new_node(n));
	}

	// Case 2: Parenthesized expression -> '(' expr ')'
	// 	- accept() checks if we are currently at a '('
	//	- If true, it consumes it and returns true.
	else if (accept(s, '('))
	{
		// Parse the expression inside the parenthesis
		node *inside = parse_expr_rec(s);
		if (!inside)
			return (NULL);
		
		// After rinishing the EXPR, we MUST see a closing ')'
		// If expect() fails, it prints an error and we must free the subtree
		if (!expect(s, ')'))
		{
			destroy_tree(inside);
			return (NULL);
		}

		// The while "(expr)" behaves as a single FACTOR.
		return (inside);
	}

	// Case 3: Not a digit AND not a '(' == invaid token 
	else
	{
		unexpected(**s);
		return (NULL);
	}
}

// This funcction parses a TERM (multiplication expression)
//		TERM = one FACTOR, followed by zero or more '* FACTOR' parts.
//
// Logic:
//	- Fist we parse a FACTOR.
//	- Then, as long as we see '*' we:
//		- Consume the '*'
//		- parse the FACTOR on the right
//		- build a MULTI node (left * right)
//		- treat that result as the new "left"
//
//	Why it works:
//	 - All multiplications are grouped together here,
//	   BEFORE we deal with '+' in parse_expr_rec().
//	 - This gives '*' HIGHER precendence than '+'.
node *parse_term(char **s)
{
	// Parse the first FACTOR on the left side of the TERM
	node *left = parse_factor(s);
	if (!left)
		return (NULL);
	
	// While we see '*', continue bulding MULTI nodes.
	while (accept(s, '*'))
	{
		node *right = parse_factor(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}

		// Create a MULTI node multiplying "left * right"
		node n;
		n.type = MULTI;
		n.val = 0;
		n.l = left;
		n.r = right;

		node *new = new_node(n);
		if (!new)
		{
			destroy_tree(left);
			destroy_tree(right);
			return (NULL);
		}

		// This new MULTI node becomes the new "left" value.
		// This lets us chain: a * b * c ...
		left = new;
	}

	// No more '*', return the full TERM tree;
	return (left);
}

// This function parses an EXPR:
//		EXPR = one TERM, followed by zero or more "+ TERM" parts.
// Logic:
// 	- First, parse a TERM
//	- Then, as long as we see a '+', we:
//		- consume the '+'
//		- parse the TERM on the right
//		- build an ADD node (left + right)
//		- treat that resul as the new "left".
//
// Why it works:
//	'+' is lower prio than '*', becuase parse_term() has already handled all multiplications.
//	So this function only deals with adding together complete TERMS.
node *parse_expr_rec(char **s)
{
	// Parse the first TERM on the left side of the expression
	node* left = parse_term(s);
	if (!left)
		return (NULL);

	// While we see '+', continue building ADD nodes.
	while (accept(s, '+'))
	{
		// Parse the TERM on the right side of '+'
		node *right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return(NULL);
		}

		// Build an ADD node combining left + right
		node n;
		n.type = ADD;
		n.val = 0;
		n.l = left;
		n.r = right;

		node *new = new_node(n);
		if (!new)
		{
			destroy_tree(left);
			destroy_tree(right);
			return (NULL);
		}

		// This newly created ADD node becomes the new "left"
		// so we can chain expressions like 1+2+3+4
		left = new;
	}

	// No more '+', return the entire expression tree.
	return (left);
}

// *s is the input string
node    *parse_expr(char *s)
{
	// Pointer to the Abstract Syntax Tree (root node)
	node *ret;
	
	// Parse the input string into a AST
	// 	- Passing in the &s, so that we can advence it as the parser consumes its characters.
	ret = parse_expr_rec(&s);
	if (!ret)
		return (NULL);

	// At this point *s points to somewhere in the original string
	// 	- If the entire string was valid and fully consumed, *s should be '\0'.
	//	- If != '\0', there was an unexpected char after a valid expression.
	//		Example: 1+2)
    if (*s) 
    {
		unexpected(*s); // Print unexpected token message.
        destroy_tree(ret);	// Destroy AST
        return (NULL);	// Return null to signal error.
    }
    return (ret);	// Valid AST built.
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
	return (0); // FIX: This was missing (silence compiler warning.)
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}