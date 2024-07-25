/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sps169 <sps169@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 07:31:41 by sps169           ###   ########.fr       */
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
	t_flags flags;

	i = 1;
	flags = init_flags();
	while (ft_strchr("dioxXucsp%", format[start + i]) == NULL)
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
		else if (ft_isdigit(format[start + i]))
		{	if (flags.period == 0)
				flags.min_width = ft_atoi(format+(start+i));
			else
				flags.precision = ft_atoi(format+(start+i));
		}
		else if (format[start + i] == '.')
			flags.period++;

	}
	return (0);
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