#ifndef VBC_H
# define VBC_H

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;


// Provided
node    *new_node(node n);
void    destroy_tree(node *n);
void    unexpected(char c);
int 	expect(char **s, char c);

// Provded but needed fix
node    *parse_expr(char *s);
int 	accept(char **s, char c);
int 	eval_tree(node *tree);

// Not provided
node 	*parse_factor(char **s);
node 	*parse_term(char **s);
node 	*parse_expr_rec(char **s);


#endif