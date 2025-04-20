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

	end = ft_strlen(s1);
	while (s1[end])
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

	start = trimstart(s1, set);
	end = trimend(s1, set);
	str = malloc(end - start + 1);
	if (!str)
		return NULL;
	ft_strlcpy(str, &s1[start], end - start);
	return str;
}
