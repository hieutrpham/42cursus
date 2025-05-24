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
#include <stdio.h>

static int has_nl(t_list *node)
{
	char *tmp;

	if (!node)
		return 0;
	while (node)
	{
		tmp = node->content;
		while (*tmp)
		{
			if (*tmp == '\n')
				return 1;
			tmp++;
		}
		node = node->next;
	}
	return 0;
}

static t_list *create_node(char *content)
{
	t_list *node;

	if (!content)
		return NULL;
	node = malloc(sizeof(t_list));
	if (!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return node;
}

static void append(t_list **node, t_list *new)
{
	t_list *tmp;

	if (!new)
		return;
	if (!*node)
	{
		*node = new;
		return;
	}
	tmp = *node;
	while ((tmp)->next)
		tmp = (tmp)->next;
	(tmp)->next = new;
}
static void build_list(int fd, t_list **node)
{
	char *buff;
	ssize_t bytes;
	t_list *new_node;

	bytes = 1;
	while (bytes > 0 && !has_nl(*node))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return;
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buff), ft_free(node));
		buff[bytes] = 0;
		new_node = create_node(buff);
		if (!new_node)
			return (free(buff), ft_free(node));
		append(node, new_node);
	}
}

t_list *get_next_line(int fd)
{
	static t_list *node;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0 , 0) < 0)
		return NULL;
	build_list(fd, &node);
	if (!node)
		return NULL;
	return node;
}
