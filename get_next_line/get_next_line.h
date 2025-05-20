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

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
typedef struct s_list {
	char *content;
	struct s_list *next;
} t_list;

void ft_free(t_list **lst);
int ft_strlen(const char *s);
char *ft_strdup(const char *s);
char *ft_strjoin(const char *s1, const char *s2);
char *get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
