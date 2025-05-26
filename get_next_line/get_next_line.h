/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:52:28 by trupham           #+#    #+#             */
/*   Updated: 2025/04/30 16:30:25 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

typedef struct s_list {
	char *content;
	struct s_list *next;
} t_list;

void ft_free(t_list **node);
char *get_next_line(int fd);
int has_nl(t_list *node);
t_list *create_node(char *content);
void append(t_list **node, t_list *new_node);
int get_length(t_list *node);
#endif
