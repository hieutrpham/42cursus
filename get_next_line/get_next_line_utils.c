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

char *ft_strdup(const char *s)
{
	char *str;
	int i;

	i = 0;
	if (!s)
		return NULL;
	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return NULL;
	while (*s)
		str[i++] = *s++;
	str[i] = 0;
	return str;
}

int has_newline(char *str)
{
	if (!str)
		return 0;
	while (*str)
	{
		if (*str == '\n')
			return 1;
		str++;
	}
	return 0;
}

char *ft_strjoin(const char *s1, const char *s2)
{
	char *str;
	int i;

	i = 0;
	if (!s1 || !s2)
		return NULL;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return NULL;
	if (has_newline((char*)s1))
	{
		while (*s1 && *s1 != '\n')
			s1++;
		s1++;
	}
	while (*s1 && *s1 != '\n')
		str[i++] = *s1++;
	while (*s2 && *s2 != '\n')
		str[i++] = *s2++;
	str[i] = 0;
	return str;
}
