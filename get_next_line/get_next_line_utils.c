/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:54:01 by trupham           #+#    #+#             */
/*   Updated: 2025/04/30 13:56:17 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void ft_free(t_list **node)
{
	t_list *tmp;

	if (!node || !*node)
		return;
	while (*node)
	{
		tmp = (*node)->next;
		free((*node)->content);
		free(*node);
		*node = tmp;
	}
	*node = NULL;
}

int has_nl(t_list *node)
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

t_list *create_node(char *content)
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

void append(t_list **node, t_list *new)
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

int get_length(t_list *node)
{
	int len;
	char *tmp;

	len = 0;
	if (!node)
		return 0;
	while (node)
	{
		tmp = (node->content);
		while (*tmp)
		{
			if (*tmp == '\n')
			{
				len++;
				return len;
			}
			tmp++;
			len++;
		}
		node = node->next;
	}
	return len;
}
