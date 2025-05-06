/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:50 by trupham           #+#    #+#             */
/*   Updated: 2025/05/06 17:01:27 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int putnbr(int c)
{
	return 0;
}

int putchar(int c)
{
	char t;

	t = (char)c;
	write(1, &t, 1);
	return 1;
}

int putstr(const char *str)
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

int ft_printf(const char *str, ...)
{
	va_list args;
	int count;

	if (!str)
		return -1;
	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if(*str == 'c')
				count += putchar(va_arg(args, int));
			if (*str == 's')
				count += putstr(va_arg(args, char *));
		}
		else
		{
			write(1, str, 1);
			count++;
		}
		str++;
	}
	va_end(args);
	return count;
}

int main()
{
	// int t = printf("hello%d\n\t\f", 123123);
	// printf("%d", t);
	int count = ft_printf("hello %c %s", 'u', "helloworld");
	printf("%d\n", count);
	return 0;
}
