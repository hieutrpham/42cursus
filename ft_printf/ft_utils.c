/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:06:23 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 17:13:09 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putchar(int c)
{
	char	t;

	t = (char)c;
	write(1, &t, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		count++;
		write(1, str++, 1);
	}
	return (count);
}

int	ft_ilen(int n)
{
	int		len;
	long	tmp;

	tmp = n;
	len = 0;
	if (tmp <= 0)
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

int	ft_ulen(unsigned int n)
{
	int		len;
	long	tmp;

	tmp = n;
	len = 0;
	if (n == 0)
		len++;
	while (tmp)
	{
		len++;
		tmp = tmp / 10;
	}
	return (len);
}
