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
#include <string.h>

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

char *get_line(t_list *node)
{
	char *line;
	int i;
	char *tmp;

	i = 0;
	line = malloc(get_length(node) + 1);
	if (!line)
		return NULL;
	while (node)
	{
		tmp = node->content;
		while (*tmp)
		{
			if (*tmp == '\n')
			{
				line[i++] = *tmp;
				return (line[i] = 0, line);
			}
			line[i++] = *tmp++;
		}
		node = node->next;
	}
	line[i] = 0;
	return line;
}

t_list *clean_node(t_list *node)
{
	t_list *clean_node;
	char *buff;
	char *tmp;
	int i;

	if (!has_nl(node))
		return NULL;
	while (node->next)
		node = node->next;
	tmp = node->content;
	while (*tmp)
	{
		if (*tmp == '\n')
		{
			tmp++;
			break;
		}
		else
			tmp++;
	}
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return NULL;
	i = 0;
	while (*tmp)
		buff[i++] = *tmp++;
	buff[i] = 0;
	clean_node = create_node(buff);
	if (!clean_node)
		return (NULL);
	return clean_node;
}

char *get_next_line(int fd)
{
	static t_list *node;
	char *line;
	t_list *new_node;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0 , 0) < 0)
		return NULL;
	build_list(fd, &node);
	if (!node)
		return NULL;
	line = get_line(node);
	if (!line || *line == 0)
		return (free(line), NULL);
	new_node = clean_node(node);
	if (!new_node)
		return NULL;
	ft_free(&node);
	node = new_node;
	return line;
}
