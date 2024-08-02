/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:31 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/02 22:26:24 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg_pointer(void *pointer, t_flags flags)
{
	t_flags	new_flags;
	char	*print;
	char	*num_str;
	int		n;

	new_flags = init_flags();
	new_flags.min_width = flags.min_width;
	new_flags.minus = flags.minus;
	if (pointer)
	{
		num_str = ft_utoa_base((unsigned long) pointer, "0123456789abcdef", new_flags);
		if (!num_str)
			return (0);
		print = ft_strjoin("0x", num_str);
		if (print)
		{
			n = justify_print(print, new_flags);
			free(num_str);
			free(print);
		}
		else
			free(num_str);
	}
	else
		n = justify_print("(nil)", new_flags);
	return (n);
}

int	justify_print(char *print, t_flags flags)
{
	int		size;
	int		diff;
	int		i;
	char	blank;
	
	size = ft_strlen(print);
	diff = flags.min_width - size;
	i = 0;
	blank = ' ';
	if (flags.zero && flags.precision == -1 && (flags.type == 'u' || flags.type == 'x' || flags.type == 'X'))
		blank = '0';
	if (diff > 0 && !flags.minus)
	{
		while (i++ < diff)
			write(1, &blank, 1);
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

int	print_arg_hex(unsigned int hex, t_flags flags, int mayus)
{
	char	*print;
	char	*aux;
	int		size;

	if (mayus)
		print = ft_utoa_base((unsigned int) hex, "0123456789ABCDEF", flags);
	else
		print = ft_utoa_base((unsigned int) hex, "0123456789abcdef", flags);
	if (!print)
	{
		write(1, "{MALLOC_ERROR}", 14);
		return (0);
	}
	if (flags.hash)
	{
		aux = print;
		print = ft_strjoin("0x", print);
		free(aux);
	}
	size = justify_print(print, flags);
	free(print);
	return (size);
}