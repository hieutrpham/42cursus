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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(int c);
int	ft_putstr(const char *str);
int	ft_putuint(unsigned int n);
int	ft_putint(int n);
int	ft_puthex(unsigned long n, char c);
int	ft_putptr(unsigned long ptr);
int	ft_ulen(unsigned int n);
int	ft_ilen(int n);
#endif
