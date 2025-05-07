/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:16:35 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 17:11:48 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int len_hex(unsigned int n)
{
	int count;

	count = 1;
	while (n > 16)
	{
		n = n / 16;
		count++;
	}
	return count;
}

static void write_hex(unsigned int n)
{
	char hex[] = "0123456789abcdef";

	if (n > 16)
		write_hex(n / 16);
	ft_putchar(hex[ n % 16 ]);
}

static void write_upper_hex(unsigned int n)
{
	char hex[] = "0123456789ABCDEF";

	if (n > 16)
		write_upper_hex(n / 16);
	ft_putchar(hex[ n % 16 ]);
}

int ft_puthex(unsigned int n, char c)
{
	if (c == 'x')
		write_hex(n);
	if (c == 'X')
		write_upper_hex(n);
	return len_hex(n);
}
