/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   justify_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:28:37 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 14:07:03 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	before_print_format(int *i, int diff, t_flags flags)
{
	char	blank;

	blank = ' ';
	if (flags.zero && flags.precision == -1
		&& (flags.type == 'u' || flags.type == 'x' || flags.type == 'X'))
		blank = '0';
	if (diff > 0 && !flags.minus)
	{
		while (*i < diff)
		{
			write(1, &blank, 1);
			*i = *i + 1;
		}
	}
}

int	justify_print(char *print, t_flags flags)
{
	int		size;
	int		diff;
	int		i;

	size = ft_strlen(print);
	diff = flags.min_width - size;
	i = 0;
	before_print_format(&i, diff, flags);
	write(1, print, size);
	if (diff > 0 && flags.minus)
	{
		while (i++ < diff)
			write(1, " ", 1);
	}
	if (diff > 0)
		return (size + diff);
	else
		return (size);
}
