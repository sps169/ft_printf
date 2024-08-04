/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:08:51 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 15:10:44 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_num_size(unsigned long num, size_t base_len, t_flags flags)
{
	int				num_size;
	unsigned long	num_cpy;

	num_size = 0;
	num_cpy = num;
	while (num_cpy > 0)
	{
		num_cpy /= base_len;
		num_size++;
	}
	if (num == 0 && (flags.precision > 0 || flags.precision == -1))
		num_size = 1;
	return (num_size);
}

static char	*allocate_string(int num_size, t_flags flags)
{
	char	*string;

	if (num_size < flags.precision && flags.precision != -1)
		string = malloc(sizeof(char) * (flags.precision + 1));
	else
		string = malloc(sizeof(char) * (num_size + 1));
	return (string);
}

static int	fill_diff(int diff, char *string, char *base, int num_size)
{
	int	i;

	i = 0;
	while (i < diff && diff > 0)
	{
		string[i] = base[0];
		i++;
	}
	string[num_size + diff] = 0;
	return (i);
}

static void	fill_digits(unsigned long num, int start_point,
				char *string, char *base)
{
	int		i;
	size_t	base_len;

	i = 1;
	base_len = ft_strlen(base);
	while (num > 0)
	{
		string[start_point - i++] = base[num % base_len];
		num = num / base_len;
	}
}

char	*ft_utoa_base(unsigned long num, char *base, t_flags flags)
{
	size_t	base_len;
	int		num_size;
	char	*string;
	int		diff;
	int		i;

	base_len = ft_strlen(base);
	num_size = calc_num_size(num, base_len, flags);
	string = allocate_string(num_size, flags);
	if (!string)
		return (NULL);
	diff = flags.precision - num_size;
	if (flags.precision == -1 || diff < 0)
		diff = 0;
	i = fill_diff(diff, string, base, num_size);
	if (num == 0 && (flags.precision > 0 || flags.precision == -1))
		string[i] = base[0];
	else
		fill_digits(num, num_size + diff, string, base);
	return (string);
}
