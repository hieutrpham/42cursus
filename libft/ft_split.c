/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:15:49 by trupham           #+#    #+#             */
/*   Updated: 2025/04/21 12:01:43 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	word_count;
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	word_count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			word_count++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (word_count);
}

static void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// return pointer to the start of the word
static const char	*get_next_word(const char *s, char c, int *len)
{
	const char	*start;
	int			i;

	i = 0;
	*len = 0;
	while (s[i] == c)
		i++;
	start = &s[i];
	while (s[i] && s[i] != c)
	{
		(*len)++;
		i++;
	}
	if (*len > 0)
		return (start);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	int			j;
	int			len;
	const char	*start;

	j = 0;
	arr = ft_calloc((count_word(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		start = get_next_word(s, c, &len);
		if (start != NULL)
		{
			arr[j] = ft_substr(start, 0, len);
			if (!arr[j])
				ft_free(arr);
			j++;
			s = start + len;
		}
		else
			s++;
	}
	return (arr);
}
/*
char	**ft_split2(char const *s, char c)
{
	char	**arr;
	int		start;
	int		i;
	int		flag;
	int		j;

	init_vars(&i, &flag, &j);
	arr = ft_calloc((count_word(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			start = i;
		}
		else if (s[i] == c && flag == 1)
		{
			flag = 0;
			arr[j++] = ft_substr(s, start, i - start);
		}
	}
	if (flag == 1)
		arr[j] = ft_substr(s, start, i - start);
	return (arr);
}
*/
