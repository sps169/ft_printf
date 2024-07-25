/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 11:49:50 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int do_printing(char type, va_list args, t_flags flags) {
	(void)args;
	(void)type;
	(void)flags;
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
	while (ft_strchr("dioxXucsp%", format[start + i]) == NULL)
		i++;
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