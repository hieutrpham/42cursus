/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:54:30 by trupham           #+#    #+#             */
/*   Updated: 2025/04/18 11:13:58 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	sum;

	sum = 0;
	if (n <= 0)
		return (0);
	while (n && (*s1 || *s2))
	{
		sum = *s1 - *s2;
		if (sum != 0)
			return (sum);
		n--;
		s1++;
		s2++;
	}
	return (sum);
}
