/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:27:35 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/25 15:19:58 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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