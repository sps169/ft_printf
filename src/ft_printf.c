/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 13:10:33 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	init_flags(void)
{
	t_flags	flags;

	flags.blank = 0;
	flags.hash = 0;
	flags.min_width = -1;
	flags.minus = 0;
	flags.period = 0;
	flags.plus = 0;
	flags.precision = -1;
	flags.type = 0;
	flags.zero = 0;
	return (flags);
}

static int	handle_conversion(char conversion, va_list args, t_flags flags)
{
	if (conversion == 'c')
		return (print_arg_char(va_arg(args, int), flags));
	else if (conversion == 's')
		return (print_arg_string(va_arg(args, char *), flags));
	else if (conversion == 'u')
		return (print_arg_unsigned_decimal(va_arg(args, unsigned int), flags));
	else if (conversion == 'i')
		return (print_arg_decimal(va_arg(args, int), flags));
	else if (conversion == 'd')
		return (print_arg_decimal(va_arg(args, int), flags));
	else if (conversion == 'p')
		return (print_arg_pointer(va_arg(args, void *), flags));
	else if (conversion == 'x')
		return (print_arg_hex(va_arg(args, unsigned int), flags, 0));
	else if (conversion == 'X')
		return (print_arg_hex(va_arg(args, unsigned int), flags, 1));
	else if (conversion == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

static int	flags_read(char const *format, va_list args, int *i)
{
	t_flags	flags;
	int		j;
	int		start;

	start = *i;
	j = 1;
	flags = init_flags();
	advance_format_flags(format + start, &flags, &j);
	advance_min_max_flags(format + start, &flags, &j, args);
	if (ft_strchr("dioxXucsp%", (format + start)[j]) == NULL)
	{
		*i += j;
		return (write(1, format + start, j));
	}
	else
	{
		flags.type = (format + start)[j];
		*i += j + 1;
		return (handle_conversion((format + start)[j], args, flags));
	}
}

int	ft_printf(char const *format, ...)
{
	va_list		args;
	int			size;
	int			i;

	size = 0;
	i = 0;
	va_start(args, format);
	while ((format) && format[i])
	{
		if (format[i] == '%')
			size += flags_read(format, args, &i);
		else
		{
			size += write(1, &(format[i]), 1);
			i++;
		}
	}
	va_end(args);
	return (size);
}
