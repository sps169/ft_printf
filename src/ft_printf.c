/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/23 20:25:27 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	flags_read(char const *format, int start)
{
	int	i;

	i = 2;
	while (ft_strchr("dioxXucsp%", format[start + i - 1]) == NULL)
		i++;
	return (i);
}

static int	handle_conversion(char const *format, va_list args)
{
	(void)format;
	(void)args;
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
			handle_conversion(format, args);
			i += flags_read(format, i);
			ft_putchar(format[i]);//
		} 
		else
		{
			ft_putchar(format[i]);
			size++;
		}
		i++;
	}
	va_end(args);
	return (size);
}