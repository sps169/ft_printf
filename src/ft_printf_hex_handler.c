/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:51:12 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 19:13:11 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*zero_string_creation(char *print, int ox, t_flags flags)
{
	int		i;
	char	*zeros;

	i = 0;
	zeros = malloc(sizeof(char)
			* ((flags.min_width - ox - ft_strlen(print)) + 1));
	if (!zeros)
		return (NULL);
	while (i + ft_strlen(print) < (size_t)flags.min_width - ox)
		zeros[i++] = '0';
	zeros[i] = 0;
	return (zeros);
}

static char	*put_zeros(unsigned int hex, char *print, t_flags flags)
{
	char	*z_print;
	char	*zeros;
	int		ox;

	ox = 2;
	if (hex == 0)
		ox = 0;
	if ((size_t)flags.min_width - ox > ft_strlen(print))
	{
		zeros = zero_string_creation(print, ox, flags);
		if (!zeros)
			return (NULL);
		z_print = ft_strjoin(zeros, print);
		free(zeros);
		free(print);
		if (!z_print)
			return (NULL);
		return (z_print);
	}
	else
		return (print);
}

static char	*insert_ox(unsigned int hex, char *print, int mayus, t_flags flags)
{
	char	*aux;
	char	*result;

	result = print;
	if (flags.hash && hex != 0)
	{
		aux = print;
		if (mayus)
			result = ft_strjoin("0X", print);
		else
			result = ft_strjoin("0x", print);
		free(aux);
	}
	return (result);
}

int	print_arg_hex(unsigned int hex, t_flags flags, int mayus)
{
	char	*print;
	int		size;

	if (mayus)
		print = ft_utoa_base((unsigned int) hex, "0123456789ABCDEF", flags);
	else
		print = ft_utoa_base((unsigned int) hex, "0123456789abcdef", flags);
	if (!print)
	{
		write(1, "{MALLOC_ERROR}", 14);
		return (0);
	}
	if (flags.hash && flags.zero && flags.min_width && flags.precision == -1)
	{
		print = put_zeros(hex, print, flags);
		if (!print)
			return (0);
	}
	print = insert_ox(hex, print, mayus, flags);
	if (!print)
		return (0);
	size = justify_print(print, flags);
	free(print);
	return (size);
}
