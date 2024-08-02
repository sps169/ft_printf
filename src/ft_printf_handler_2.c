/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:15:08 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/02 22:28:10 by sperez-s         ###   ########.fr       */
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
		while ((writen < flags.min_width - 1 && !flags.minus) 
			|| (writen < flags.min_width && flags.minus))
			writen += write(1, " ", 1);
	}
	if (!flags.minus)
		writen += write(1, &character, 1);
	return (writen);
}

int	print_arg_string(char *string, t_flags flags)
{
	char	*print;

	if (!string)
	{
		if (flags.precision >= 6 || flags.precision == -1)
			return (justify_print("(null)", flags));
		else
			return (justify_print("", flags));
	}
	if (flags.precision < (int) ft_strlen(string) && flags.precision != -1)
	{
		print = ft_substr(string, 0, flags.precision);
		if (!print)
			return (0);
	} else
		print = string;
	return (justify_print(print, flags));
}

int	print_arg_decimal(int decimal, t_flags flags)
{
	char	*pointer;
	int		printed;

	pointer = ft_itoa(decimal, flags);
	if (!pointer)
	{
		write(1, "{MALLOC_ERROR}", 14);
		return (0);
	}
	printed = justify_print(pointer, flags);
	free(pointer);
	return (printed);
}