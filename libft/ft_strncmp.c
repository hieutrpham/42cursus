/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:54:30 by trupham           #+#    #+#             */
/*   Updated: 2025/04/23 16:00:21 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int					sum;
	const unsigned char	*l1;
	const unsigned char	*l2;

	l1 = (const unsigned char *)s1;
	l2 = (const unsigned char *)s2;
	sum = 0;
	while (n && (*l1 || *l2))
	{
		sum = *l1 - *l2;
		if (sum != 0)
			break ;
		n--;
		l1++;
		l2++;
	}
	return (sum);
}
