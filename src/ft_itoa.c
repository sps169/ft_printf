/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:27:47 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/02 23:12:14 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_total_int_digits(int n, int precision)
{
	int	digits;

	digits = 0;
	if (n == 0 && precision == 0)
		return (0);
	while (n / 10 != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits + 1);
}

static char	*fill_ascii(int n, int size, t_flags flags)
{
	char	*ascii_n;
	int		digit;
	int		is_neg;

	is_neg = 0;
	ascii_n = malloc((size + 1) * sizeof(char));
	if (ascii_n == NULL)
		return (NULL);
	ascii_n[size] = 0;
	size--;
	if (n < 0)
	{
		is_neg = 1;
		ascii_n[0] = '-';
	}
	if (n >= 0 && flags.blank)
		ascii_n[0] = ' ';
	if (n >= 0 && flags.plus)
		ascii_n[0] = '+';
	while (n != 0)
	{
		digit = (n % 10);
		if (digit < 0)
			digit *= -1;
		ascii_n[size] = digit + '0';
		size--;
		n = n / 10;
	}
	while (size > 0 || (size == 0 && !is_neg && !flags.blank && !flags.plus))
		ascii_n[size--] = '0';
	return (ascii_n);
}

char	*ft_itoa(int n, t_flags flags)
{
	char	*ascii_n;
	int		size;

	ascii_n = NULL;
	size = get_total_int_digits(n, flags.precision);
	if (size < flags.precision && flags.precision != -1)
		size = flags.precision;
	else if (size < flags.min_width && flags.zero && flags.precision == -1 && !flags.minus)
	{
		size = flags.min_width;
		if (n < 0 || flags.blank || flags.plus)
			size--;
	}
	if (n < 0 || flags.blank || flags.plus)
		size++;
	ascii_n = fill_ascii(n, size, flags);
	return (ascii_n);
}