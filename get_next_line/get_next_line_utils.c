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
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return str;
}

void ft_free(t_list **lst)
{
	 t_list *tmp;

	if (!*lst || !lst)
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free((*lst));
		*lst = tmp;
	}
	*lst = NULL;
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

