/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:33:41 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 14:20:03 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_ilen(int n)
{
	int		len;
	long	tmp;

	tmp = n;
	len = 0;
	if (tmp < 0)
	{
		tmp = -tmp;
		len++;
	}
	while (tmp)
	{
		len++;
		tmp = tmp / 10;
	}
	return (len);
}

static int	ft_ulen(unsigned int n)
{
	int		len;
	long	tmp;

	tmp = n;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp / 10;
	}
	return (len);
}

static void	write_int(int n)
{
	long	tmp;

	tmp = (long)n;
	if (tmp < 0)
	{
		ft_putchar('-');
		tmp = -tmp;
	}
	if (tmp > 9)
		write_int(tmp / 10);
	ft_putchar((tmp % 10) + '0');
}

static void	write_uint(unsigned int n)
{
	long	tmp;

	tmp = (long)n;
	if (tmp > 9)
		write_int(tmp / 10);
	ft_putchar((tmp % 10) + '0');
}

int ft_putint(int n)
{
	write_int(n);
	return ft_ilen(n);
}

int ft_putuint(unsigned int n)
{
	write_uint(n);
	return ft_ulen(n);
}
