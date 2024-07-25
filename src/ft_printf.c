/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 13:55:19 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int do_printing(char type, va_list arg, t_flags flags) {
	if (type == 'c') //-5
		return (print_arg_char(va_arg(arg, int), flags));
	else if (type == 's')//-5.1
		return (print_arg_string(va_arg(arg, char *), flags));
	else if (type == 'i')//+-0 5.1
		return (print_arg_decimal(va_arg(arg, int), flags));
	else if (type == 'p')//-5
		return (print_arg_pointer(va_arg(arg, void *), flags));
	else if (type == 'd')//+-0 5.1
		return (print_arg_decimal(va_arg(arg, int), flags));
	else if (type == 'u')//-05.1
		return (print_arg_unsigned_decimal(va_arg(arg, unsigned int), flags));
	else if (type == 'x')//-0#5.1
		return (print_arg_hex(va_arg(arg, unsigned int), flags));
	else if (type == 'X')//-0#5.1
		return (print_arg_hex_mayus(va_arg(arg, unsigned int), flags));
	else if (type == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

static t_flags init_flags()
{
	t_flags flags;
	flags.blank = 0;
	flags.hash = 0;
	flags.min_width = 0;
	flags.minus = 0;
	flags.period = 0;
	flags.plus = 0;
	flags.precision = 0;
	flags.type = 0;
	flags.zero = 0;
	return (flags);
}

static int	flags_read(char const *format, int start)
{
	int	i;

	i = 1;
	while (format[start + i] && ft_strchr("dioxXucsp%", format[start + i]) == NULL)
		i++;
	if (!format[start + i])
		return (i);
	else	
		return (i + 1);
}

static int	handle_conversion(char const *format, va_list args, size_t start)
{
	size_t	i;
	size_t	j;
	t_flags flags;

	i = 1;
	flags = init_flags();
	while (format[start + i] && ft_strchr("dioxXucsp%", format[start + i]) == NULL && ft_strchr("+0-# ", format[start + i]) != NULL)
	{
		if (format[start + i] == '-')
			flags.minus++;
		else if (format[start + i] == '+')
			flags.plus++;
		else if (format[start + i] == '0')
			flags.zero++;
		else if (format[start + i] == ' ')
			flags.blank++;
		else if (format[start + i] == '#')
			flags.hash++;
		i++;
	}
	while (format[start + i] && ft_strchr("dioxXucsp%", format[start + i]) == NULL && (ft_isdigit(format[start + i])))
	{
		if (flags.min_width == 0)
			flags.min_width = ft_atoi(format + (start + i));
		i++;
	}
	if (format[start + i] && ft_strchr("dioxXucsp%", format[start + i]) == NULL && format[start + i] == '.')
	{
		flags.period++;
		i++;
	}
	while (format[start + i] && ft_strchr("dioxXucsp%", format[start + i]) == NULL && (ft_isdigit(format[start + i])))
	{
		if (flags.precision == 0)
			flags.precision = ft_atoi(format+(start+i));
		i++;
	}
	if (format[start + i] && ft_strchr("dioxXucsp%", format[start + i]) != NULL)
	{
		write(1, "GOOD\n", 5);
		return (do_printing(format[start + i], args, flags));
	}
	else
	{
		write(1, "BAD\n", 5);
		j = 0;
		while(format[start + j] && j <= i)
		{
			ft_putchar(format[start + j]);
			j++;
		}
		return (flags_read(format, start));
	}
}

int	ft_printf(char const *format, ...)
{
	va_list		args;
	int			size;
	size_t		i;

	size = 0;
	i = 0;
	va_start(args, format);
	while ((format) && i < ft_strlen(format))
	{
		if (format[i] == '%')
		{
			size += handle_conversion(format, args, i);
			i += flags_read(format, i);
		} 
		else
		{
			ft_putchar(format[i]);
			size++;
			i++;
		}
	}
	va_end(args);
	return (size);
}