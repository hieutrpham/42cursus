/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:41:12 by trupham           #+#    #+#             */
/*   Updated: 2025/05/08 10:22:28 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_F
#define FT_PRINT_F

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h> // WARN: use for debug
#include <stdlib.h>
#include <stdint.h>

int ft_printf(const char *str, ...);
int ft_putchar(int c);
int ft_putstr(const char *str);
int ft_putuint(unsigned int n);
int ft_putint(int n);
int ft_puthex(uintptr_t n, char c);
int ft_putptr(uintptr_t ptr);
#endif // !FT_PRINT_F
