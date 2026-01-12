#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include "vbc.h"

void check_err(node *n)
{
	if (!n)
		exit(1);
}

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
    if (**s == c)
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

node *parse_addition(char **s);
node *parse_multi(char **s);

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
		(*s)++;
		return (new_node(n));
	}
	else if (accept(s, '('))
	{
		node *inside = parse_addition(s);
		if (!inside)
			return NULL;
		expect(s, ')');
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
		check_err(right);
		node n;
		n.type = ADD;
		n.val = 0;
		n.l = left;
		n.r = right;
		node *new = new_node(n);
		check_err(new);
		left = new;
	}
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
		check_err(right);
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
	check_err(ret);
	if (*s)
	{
		printf("test\n");
		unexpected(*s);
		destroy_tree(ret);
		return NULL;
	}
	return ret;
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
