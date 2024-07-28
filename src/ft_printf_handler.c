/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:31 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/28 17:11:19 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg_pointer(void *pointer, t_flags flags)
{
	(void)flags;
	int	n;

	write(1, "0x", 2);
	n = ft_putnbr_base((unsigned long) pointer, "0123456789abcdef", 16);
	return (2 + n);
}

int	justify_print(char *print, t_flags flags)
{
	int		size;
	int		diff;
	int		i;
	
	size = ft_strlen(print);
	diff = flags.min_width - size;
	i = 0;
	if (diff > 0 && !flags.minus)
	{
		while (i++ < diff)
			write(1, " ", 1);
	}
	write(1, print, size);
	if (diff > 0 && flags.minus)
	{
		while (i++ < diff)
			write(1, " ", 1);
	}
	if (diff > 0)
		return (size + diff);
	else
		return (size);
}

int	print_arg_unsigned_decimal(unsigned int decimal, t_flags flags)
{
	char	*print;
	int		size;

	print = ft_utoa_base((unsigned int) decimal, "0123456789", flags);
	if (!print)
	{
		write(1, "{MALLOC_ERROR}", 14);
		return (0);
	}
	size = justify_print(print, flags);
	free(print);
	return (size);

}

int	print_arg_hex(unsigned int hex, t_flags flags)
{
	(void)flags;
	int	n;

	n = ft_putnbr_base(hex, "0123456789abcdef", 16);
	return (n);
}

int	print_arg_hex_mayus(unsigned int hex, t_flags flags)
{
	(void)flags;
	int	n;

	n = ft_putnbr_base(hex, "0123456789ABCDEF", 16);
	return (n);
}