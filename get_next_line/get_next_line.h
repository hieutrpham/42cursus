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

# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
typedef struct s_list {
	char *content;
	struct s_list *next;
} t_list;

int isnewline(char *str);
t_list *create_node(void *content);
void	append(t_list **lst, t_list *new_node);
t_list *get_next_line(int fd);
int ft_strlen(const char *s);
char *ft_strdup(const char *s);
char *ft_strjoin(const char *s1, const char *s2);
t_list *get_next_line(int fd);
#endif
