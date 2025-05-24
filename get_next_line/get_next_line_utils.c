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

