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

static t_list *create_node(void *content)
{
	t_list *new_node;

	if (!content)
		return NULL;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return NULL;
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}

static void	append(t_list **lst, t_list *new)
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

static char *build_line(t_list **lst)
{
	char *line;
	t_list *tmp;

	line = "";
	tmp = *lst;
	if (has_newline(tmp->content))
	{
		while (*(tmp->content) != '\n')
			(tmp->content)++;
		(tmp->content)++;
		line = ft_strdup(tmp->content);
		if (!line)
			return (ft_free(lst), NULL);
		tmp = tmp->next;
	}
	while (tmp)
	{
		line = ft_strjoin(line, tmp->content);
		if (!line)
			return (ft_free(lst), NULL);
		if (has_newline(tmp->content))
			break;
		tmp = tmp->next;
	}
	*lst = tmp;
	return line;
}

char *get_next_line(int fd)
{
	t_list *node;
	static t_list *head;
	char str[BUFFER_SIZE + 1];
	ssize_t bytes;

	while (1)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes <= 0)
			return NULL;
		str[bytes] = 0;
		node = create_node(ft_strdup(str));
		if (!node)
			return (ft_free(&head), NULL);
		append(&head, node);
		if (has_newline(node->content) || bytes < BUFFER_SIZE)
			break;
	}
	return build_line(&head);
}
