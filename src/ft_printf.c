/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/28 17:38:25 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags init_flags()
{
	t_flags flags;
	flags.blank = 0;
	flags.hash = 0;
	flags.min_width = 0;
	flags.minus = 0;
	flags.period = 0;
	flags.plus = 0;
	flags.precision = -1;
	flags.type = 0;
	flags.zero = 0;
	return (flags);
}

static void	advance_format_flags(char const *format, t_flags *flags, int *j)
{
	while (format[*j] && ft_strchr("+-0 #",format[*j]))
	{
		if (format[*j] == '+')
			(*flags).plus++;
		else if (format[*j] == '-')
			(*flags).minus++;
		else if (format[*j] == '0')
			(*flags).zero++;
		else if (format[*j] == ' ')
			(*flags).blank++;
		else if (format[*j] == '#')
			(*flags).hash++;
		*j = *j + 1;
	}
}

static void	advance_min_max_flags(char const *format, t_flags *flags, int *j)
{
	while (format[*j] && ft_isdigit(format[*j]))
	{
		if ((*flags).min_width == 0)
			(*flags).min_width = ft_atoi(format + *j);
		*j = *j + 1;
	}
	if (format[*j] && format[*j] == '.')
	{
		(*flags).period++;
		*j = *j + 1;
	}
	while (format[*j] && ft_isdigit(format[*j]) && (*flags).period > 0)
	{
		if ((*flags).precision == -1)
			(*flags).precision = ft_atoi(format + *j);
		*j = *j + 1;
	}
}

static int	handle_conversion(char conversion, va_list args, t_flags flags)
{
	if (conversion == 'c') //-5
		return (print_arg_char(va_arg(args, int), flags));
	else if (conversion == 's')//-5.1
		return (print_arg_string(va_arg(args, char *), flags));
	else if (conversion == 'u')//-05.1
		return (print_arg_unsigned_decimal(va_arg(args, unsigned int), flags));
	else if (conversion == 'i')//+-0 5.1
		return (print_arg_decimal(va_arg(args, int), flags));
	else if (conversion == 'd')//+-0 5.1
		return (print_arg_decimal(va_arg(args, int), flags));
	else if (conversion == 'p')//-5
		return (print_arg_pointer(va_arg(args, void *), flags));
	else if (conversion == 'x')//-0#5.1
		return (print_arg_hex(va_arg(args, unsigned int), flags));
	else if (conversion == 'X')//-0#5.1
		return (print_arg_hex_mayus(va_arg(args, unsigned int), flags));
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
	advance_min_max_flags(format + start, &flags, &j);
	if (ft_strchr("dioxXucsp%", (format + start)[j]) == NULL)
	{
		*i += j;
		return (write(1, format + start, j));
	}
	else
	{
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
			ft_putchar(format[i]);
			size++;
			i++;
		}
	}
	va_end(args);
	return (size);
}