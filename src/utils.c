/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:27:35 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/02 22:13:12 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	else
		return (NULL);
}

int	ft_nbr_writer(unsigned long num, char *base, size_t base_len)
{
	int	n;

	n = 0;
	if (num > 0)
	{
		n = ft_nbr_writer(num / base_len, base, base_len);
		n += write(1, &base[num % base_len], 1);
	}
	return (n);
}

int	ft_putnbr_base(unsigned long num, char *base, size_t base_len)
{
	int	n;

	n = 0;
	if (num == 0)
		return (write(1, "0", 1));
	n = ft_nbr_writer(num, base, base_len);
	return (n);
}

char	*ft_utoa_base(unsigned long num, char *base, t_flags flags)
{
	size_t			base_len;
	int				num_size;
	unsigned long	num_cpy;
	char			*string;

	num_size = 0;
	num_cpy = num;
	base_len = ft_strlen(base);
	while (num_cpy > 0)
	{
		num_cpy /= base_len;
		num_size++;
	}
	if (num == 0 && (flags.precision > 0 || flags.precision == -1))
		num_size = 1;
	if (num_size < flags.precision && flags.precision != -1)
		string = malloc(sizeof(char) * (flags.precision + 1));
	else
		string = malloc(sizeof(char) * (num_size + 1));
	if (!string)
		return (NULL);

	int diff;
	int i;

	diff = flags.precision - num_size;
	if (flags.precision == -1 || diff < 0)
		diff = 0;
	i = 0;
	while (i < diff && diff > 0)
	{
		string[i] = base[0];
		i++;
	}
	string[num_size + diff] = 0;
	if (num == 0 && (flags.precision > 0 || flags.precision == -1))
		string[i] = base[0];
	else
	{
		i = 1;
		while (num > 0)
		{
			string[num_size + diff - i++] = base[num % base_len];
			num = num / base_len;
		}
	}
	return (string);
}