/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:56:11 by trupham           #+#    #+#             */
/*   Updated: 2025/04/30 16:50:12 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int isnewline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return 1;
		str++;
	}
	return 0;
}

t_list *create_node(void *content)
{
	t_list *new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return NULL;
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}

void	append(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_list *get_next_line(int fd)
{
	t_list *node;
	t_list *head;
	static char str[BUFFER_SIZE + 1];
	ssize_t bytes;

	head = NULL;
	bytes = read(fd, str, BUFFER_SIZE);
	if (bytes <= 0)
		return NULL;
	str[bytes] = 0;
	node = create_node(ft_strdup(str));
	append(&head, node);
	return head;
}
