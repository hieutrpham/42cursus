/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:41:12 by trupham           #+#    #+#             */
/*   Updated: 2025/05/07 10:43:03 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_F
#define FT_PRINT_F

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h> // WARN: use for debug

int ft_printf(const char *str, ...);
int ft_putchar(int c);
int ft_putstr(const char *str);
int checktype(char c, va_list *args);
#endif // !FT_PRINT_F
