/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:31 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 18:51:08 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_non_void_pt(void *pointer, t_flags f)
{
	char	*num_str;
	char	*print;
	int		n;

	n = 0;
	num_str = ft_utoa_base((unsigned long) pointer, "0123456789abcdef", f);
	if (!num_str)
		return (0);
	print = ft_strjoin("0x", num_str);
	if (print)
	{
		n = justify_print(print, f);
		free(num_str);
		free(print);
	}
	else
		free(num_str);
	return (n);
}

int	print_arg_pointer(void *pointer, t_flags flags)
{
	t_flags	f;
	int		n;

	n = 0;
	f = init_flags();
	f.min_width = flags.min_width;
	f.minus = flags.minus;
	if (pointer)
		n = print_non_void_pt(pointer, f);
	else
		n = justify_print("(nil)", f);
	return (n);
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
