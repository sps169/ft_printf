/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:15:08 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 17:29:39 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg_char(char character, t_flags flags)
{
	int	writen;

	writen = 0;
	if (flags.minus)
		writen += write(1, &character, 1);
	if (flags.min_width > 0)
	{
		while (writen < flags.min_width - 1)
			writen += write(1, " ", 1);
	}
	if (!flags.minus)
		writen += write(1, &character, 1);
	return (writen);
}

static int	print_null_string(t_flags flags)
{
	int	writen;

	writen = 0;
	char null[] = "(null)";
	if (flags.precision == 0 || flags.precision >= 6)
	{
		if (flags.minus)
			writen += write(1, null, ft_strlen(null));
	}
	while (writen < flags.min_width)
		writen += write(1, " ", 1);
	return (writen);
}

int	print_arg_string(char *string, t_flags flags)
{
	int	to_write;
	int	i;
	int	writen;

	i = 0;
	if (!string)
		return (print_null_string(flags));
	if (ft_strlen(string) < (size_t) flags.precision || flags.precision == 0)
		to_write = ft_strlen(string);
	else if (ft_strlen(string) >= (size_t) flags.precision)
		to_write = flags.precision;
	if (flags.minus)
	{
		while (string[i] && i < to_write)
			writen += write(1, &string[i++], 1);
		while (writen < flags.min_width)
			writen += write(1, " ", 1);
	}
	else
	{
		while (writen + to_write < flags.min_width)
			writen += write(1, " ", 1);
		while (string[i] && i < to_write)
			writen += write(1, &string[i++], 1);
	}
	return (writen);
}

int	print_arg_decimal(int decimal, t_flags flags)
{
	char	*pointer;
	size_t	len;
	int		printed;

	(void)flags;
	pointer = ft_itoa(decimal);
	len = ft_strlen(pointer);
	printed = write(1, pointer, len);
	free(pointer);
	return (printed);
}