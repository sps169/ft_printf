/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:01 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 13:51:22 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	advance_format_flags(char const *format, t_flags *flags, int *j)
{
	while (format[*j] && ft_strchr("+-0 #", format[*j]))
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

static void	precision_handling(char const *format,
				t_flags *flags, int *j, va_list args)
{
	int	va_arg;

	if (format[*j] && format[*j] == '.')
	{
		(*flags).period++;
		(*flags).precision = 0;
		*j = *j + 1;
	}
	if (format[*j] && format[*j] == '*' && (*flags).period > 0)
	{
		va_arg = va_arg(args, int);
		if (va_arg < 0)
		{
			va_arg = -1;
		}
		(*flags).precision = va_arg;
		*j = *j + 1;
	}
	while (format[*j] && ft_isdigit(format[*j]) && (*flags).period > 0)
	{
		if ((*flags).precision == 0)
			(*flags).precision = ft_atoi(format + *j);
		*j = *j + 1;
	}
}

void	advance_min_max_flags(char const *format,
			t_flags *flags, int *j, va_list args)
{
	int	va_arg;

	if (format[*j] && format[*j] == '*')
	{
		va_arg = va_arg(args, int);
		if (va_arg < 0)
		{
			va_arg *= -1;
			(*flags).minus++;
		}
		(*flags).min_width = va_arg;
		*j = *j + 1;
	}
	while (format[*j] && ft_isdigit(format[*j]))
	{
		if ((*flags).min_width == -1)
			(*flags).min_width = ft_atoi(format + *j);
		*j = *j + 1;
	}
	precision_handling(format, flags, j, args);
}
