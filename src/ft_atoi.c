/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sps169 <sps169@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:09:50 by sps169            #+#    #+#             */
/*   Updated: 2024/07/23 22:11:31 by sps169           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	negative;
	long	number;

	i = 0;
	negative = 1;
	number = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + str[i++] - '0';
		if (number > 2147483647 && negative == 1)
			return (-1);
		else if (number > 2147483647L + 1L && negative == -1)
			return (0);
	}
	return ((int)(number * negative));
}