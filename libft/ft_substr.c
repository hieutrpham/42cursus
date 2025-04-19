/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:25:25 by trupham           #+#    #+#             */
/*   Updated: 2025/04/19 18:33:46 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t s_len;
	char *str;
	size_t i;

	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len || start + len >= s_len)
		return NULL;
	str = malloc(len + 1);
	if (!str)
		return NULL;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return str;
}
