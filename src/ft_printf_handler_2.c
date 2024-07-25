/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:15:08 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 13:23:20 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg_char(char character, t_flags flags)
{
	return (write(1, &character, 1));
}

int	print_arg_string(char *string, t_flags flags)
{
	if (string == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
	{
		ft_putstr_fd(string, 1);
		return (ft_strlen(string));
	}
}

int	print_arg_decimal(int decimal, t_flags flags)
{
	char	*pointer;
	size_t	len;
	int		printed;

	pointer = ft_itoa(decimal);
	len = ft_strlen(pointer);
	printed = write(1, pointer, len);
	free(pointer);
	return (printed);
}