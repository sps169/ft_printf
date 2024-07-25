/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:31 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 13:23:21 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg_pointer(void *pointer, t_flags flags)
{
	int	n;

	ft_putstr_fd("0x", 1);
	n = ft_putnbr_base((unsigned long) pointer, "0123456789abcdef", 16);
	return (2 + n);
}

int	print_arg_unsigned_decimal(unsigned int decimal, t_flags flags)
{
	return (ft_putnbr_base((unsigned int) decimal, "0123456789", 10));
}

int	print_arg_hex(unsigned int hex, t_flags flags)
{
	int	n;

	n = ft_putnbr_base(hex, "0123456789abcdef", 16);
	return (n);
}

int	print_arg_hex_mayus(unsigned int hex, t_flags flags)
{
	int	n;

	n = ft_putnbr_base(hex, "0123456789ABCDEF", 16);
	return (n);
}