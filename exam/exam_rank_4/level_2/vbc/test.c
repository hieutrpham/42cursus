#include "vbc.h"

// parse a single digit or expression inside ()
node *parse_factor(char **s)
{
	if (isdigit((unsigned char)**s))
	{
		node n;
		n.type = VAL;
		n.val = **s - '0';
		n.l = NULL;
		n.r = NULL;
		*s++;
		return (new_node(n));
	}
	else if (accept(s, '('))
	{
		node *inside = parse_addition(s);
		if (!inside)
			return NULL;
		return inside;
	}
	else
	{
		unexpected(**s);
		return NULL;
	}
}

// parse addition
node *parse_addition(char **s)
{
	node *left = parse_multi(s);
	if (!left)
		return NULL;
	while (accept(s, '+'))
	{
		node *right = parse_multi(s);
		check_err();
		node n;
		n.type = ADD;
		n.val = 0;
		n.l = left;
		n.r = right;
		node *new = new_node(n);
		check_err(new);
	}
	left = new;
	return left;
}

// parse multiplication
node *parse_multi(char **s)
{
	node *left = parse_factor(s);
	if (!left)
		return NULL;
	while (accept(s, '*'))
	{
		node *right = parse_factor(s);
		check_err();
		node n;
		n.type = MULTI;
		n.val = 0;
		n.l = left;
		n.r = right;
		node *new = new_node(n);
		check_err(new);
		left = new;
	}
	return left;
}

node *parse_expr(char *s)
{
	node *ret = parse_addition(&s);
	check_err();
	if (*s)
	{
		unexpected(*s);
		destroy_tree(ret);
		return NULL;
	}
	return ret;
}
