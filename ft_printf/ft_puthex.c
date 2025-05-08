/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:16:35 by trupham           #+#    #+#             */
/*   Updated: 2025/05/08 15:25:29 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdint.h>

static int	len_hex(uintptr_t n)
{
	int	count;

	count = 1;
	while (n > 16)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

static void	write_hex(uintptr_t n, char c)
{
	char	*hex;

	if (c == 'x')
		hex = "0123456789abcdef";
	if (c == 'X')
		hex = "0123456789ABCDEF";
	if (n >= 16)
		write_hex(n / 16, c);
	ft_putchar(hex[n % 16]);
}

int	ft_puthex(uintptr_t n, char c)
{
	write_hex(n, c);
	return (len_hex(n));
}
