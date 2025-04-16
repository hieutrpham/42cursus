/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:59 by trupham           #+#    #+#             */
/*   Updated: 2025/04/16 11:58:17 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;

	dest_tmp = dest;
	src_tmp = src;
	if (src >= dest)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			*(dest_tmp + n - 1) = *(src_tmp + n - 1);
			n--;
		}
	}
	return (dest_tmp);
}
int	main(void)
{
	char	srcdest[20] = "01234";
	char	ftsrcdest[20] = "01234";

	if (!strcmp((char *)memmove(srcdest + 2, srcdest, 7),
			(char *)ft_memmove(ftsrcdest + 2, ftsrcdest, 7)))
		printf("OK: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	else
		printf("Try again: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	if (!strcmp((char *)memmove(srcdest + 4, srcdest, 7),
			(char *)ft_memmove(ftsrcdest + 4, ftsrcdest, 7)))
		printf("OK: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	else
		printf("Try again: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	if (!strcmp((char *)memmove(srcdest, srcdest + 8, 7),
			(char *)ft_memmove(ftsrcdest, ftsrcdest + 8, 7)))
		printf("OK: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	else
		printf("Try again: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	if (!strcmp((char *)memmove(srcdest + 2, srcdest, 0),
			(char *)ft_memmove(ftsrcdest + 2, ftsrcdest, 0)))
		printf("OK: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	else
		printf("Try again: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	if (!strcmp((char *)memmove(srcdest, srcdest, 5),
			(char *)ft_memmove(ftsrcdest, ftsrcdest, 5)))
		printf("OK: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
	else
		printf("Try again: expected \"%s\", got \"%s\".\n", srcdest, ftsrcdest);
}
