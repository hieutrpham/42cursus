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

static int	issep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_word(const char *s, char c)
{
	int	word_count;
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	word_count = 0;
	while (s[i] && issep(s[i], c))
		i++;
	while (s[i])
	{
		if (!issep(s[i], c) && flag == 0)
		{
			flag = 1;
			word_count++;
		}
		else if (issep(s[i], c))
			flag = 0;
		i++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		start;
	int		i;
	int		flag;
	int		j;

	j = 0;
	flag = 0;
	i = -1;
	arr = ft_calloc((count_word(s, c) + 1), sizeof(char *));
	while (s[++i])
	{
		if (!issep(s[i], c) && flag == 0)
		{
			flag = 1;
			start = i;
		}
		else if (issep(s[i], c) && flag == 1)
		{
			flag = 0;
			arr[j] = ft_substr(s, start, i - start);
			j++;
		}
	}
	if (flag == 1)
		arr[j] = ft_substr(s, start, i - start);
	return (arr);
}
