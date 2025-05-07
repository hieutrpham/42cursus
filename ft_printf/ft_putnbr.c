/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:33:41 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 11:45:12 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_len(int n)
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

static void	write_nbr(int n)
{
	long	tmp;

	tmp = (long)n;
	if (tmp < 0)
	{
		ft_putchar('-');
		tmp = -tmp;
	}
	if (tmp > 9)
		write_nbr(tmp / 10);
	ft_putchar((tmp % 10) + '0');
}

int ft_putnbr(int n)
{
	write_nbr(n);
	return ft_len(n);
}
