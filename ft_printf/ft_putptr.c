/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:33:56 by trupham           #+#    #+#             */
/*   Updated: 2025/05/08 11:52:12 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int ft_putptr(uintptr_t ptr)
{
	int count = 2;

	ft_putstr("0x");
	count += ft_puthex(ptr, 'x');
	return count;
}
