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
// FIX: count up to \n only. create a new function
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len)
		len = s_len;
	if (s_len - start < len)
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}

