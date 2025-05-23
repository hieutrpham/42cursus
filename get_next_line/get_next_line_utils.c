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

int has_nl(const char *str)
{
	if (!str || ft_strlen(str) == 0)
		return 0;
	while (*str)
	{
		if (*str == '\n')
			return 1;
		str++;
	}
	return 0;
}

int ft_strlen(const char *s)
{
	int len;

	len = 0;
	if (!s)
		return -1;
	while (*s++)
		len++;
	return len;
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	int i;
	int j;

	if (!s2)
		return NULL;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return NULL;
		s1[0] = '\0';
	}
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	free(s1);
	return str;
}
