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

int	ft_putptr(uintptr_t ptr)
{
	int	count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	count = 2;
	ft_putstr("0x");
	count += ft_puthex(ptr, 'x');
	return (count);
}
