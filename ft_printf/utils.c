/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:06:23 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 10:43:36 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int ft_putchar(int c)
{
	char t;

	t = (char)c;
	write(1, &t, 1);
	return 1;
}

int ft_putstr(const char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		count++;
		write(1, str++, 1);
	}
	return count;
}
