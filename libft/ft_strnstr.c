/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:47:26 by trupham           #+#    #+#             */
/*   Updated: 2025/04/18 14:13:36 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *smol, size_t len)
{
	int	i;
	int	j;
	int	tmplen;

	i = 0;
	if (ft_strncmp(smol, "", sizeof(smol)) == 0)
		return ((char *)big);
	while (big[i] && len)
	{
		j = 0;
		tmplen = len;
		while (tmplen && smol[j] && big[i + j] && smol[j] == big[i + j])
		{
			j++;
			tmplen--;
		}
		if (!smol[j])
			return (&((char *)big)[i]);
		i++;
		len--;
	}
	return (NULL);
}
