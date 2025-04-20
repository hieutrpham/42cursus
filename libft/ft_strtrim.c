/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:47:06 by trupham           #+#    #+#             */
/*   Updated: 2025/04/20 10:47:48 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	istrim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return 1;
		i++;
	}
	return 0;
}

static int trimstart(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start])
	{
		if (istrim(s1[start], set))
			start++;
		else
			break;
	}
	return (start);
}

static int trimend(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (end > 0)
	{
		if (istrim(s1[end], set))
			end--;
		else
			break;
	}
	return end;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;
	int		str_len;

	i = 0;
	start = trimstart(s1, set);
	end = trimend(s1, set);
	str_len = end - start;
	if (str_len < 0)
		return (char*)ft_calloc(1, 1);
	str = malloc(str_len + 2);
	if (!str)
		return NULL;
	while (i <= str_len)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = 0;
	return str;
}
