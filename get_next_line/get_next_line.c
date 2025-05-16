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
	// printf(YELLOW"temp: "RESET);
	// printf("%s\n", tmp->content);
	if (has_newline(tmp->content))
		line = ft_strjoin(tmp->content, "");
	while (tmp)
	{
		line = ft_strjoin(line, tmp->content);
		if (has_newline(tmp->content))
			break;
		tmp = tmp->next;
	}
	// printf("%s\n", line);
	*lst = tmp;
	printf(GREEN"head:"RESET);
	printf("%s--", (*lst)->content);
	return line;
}

char *get_next_line(int fd)
{
	t_list *node;
	static t_list *head;
	char str[BUFFER_SIZE + 1];
	ssize_t bytes;

	if (head)
		printf("read head: %s\n", head->content);
	while (1)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes <= 0)
			return NULL;
		str[bytes] = 0;
		// printf("%s\n", str);
		// printf("%d\n", ft_strlen(str));
		node = create_node(ft_strdup(str));
		append(&head, node);
		//printf("%s\n", node->content);
		if (has_newline(node->content))
			break;
	}
	return build_line(&head);
}
