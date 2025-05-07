/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:50 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 13:47:27 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int checktype(char c, va_list *args)
{
	if (c == 'c')
		return ft_putchar(va_arg(*args, int));
	else if (c == 's')
		return ft_putstr(va_arg(*args, char *));
	else if (c == '%')
		return write(1, "%", 1);
	else if (c == 'd' || c == 'i')
		return ft_putnbr(va_arg(*args, int));
	return -1;
}

static void t_print(const char *str, va_list *args, int *count)
{
	int type;

	while (*str)
	{
		if (*str == '%')
		{
			str++;
			type = checktype(*str, args);
			if (type == -1)
				return;
			else
				*count += type;
		}
		else
		{
			write(1, str, 1);
			(*count)++;
		}
		str++;
	}
}

int ft_printf(const char *str, ...)
{
	va_list args;
	int count;

	if (!str)
		return -1;
	count = 0;
	va_start(args, str);
	t_print(str, &args, &count);
	va_end(args);
	return count;
}
