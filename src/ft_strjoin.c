/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:42:08 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/04 14:00:41 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_str_len(char const *s)
{
	size_t	len;

	len = 0;
	if (s != NULL)
	{
		while (s[len] != 0)
			len++;
	}
	return (len);
}

static char	*do_join(size_t s1_s, size_t s2_s, char const *s1, char const *s2)
{
	unsigned int	i;
	char			*result;

	i = 0;
	result = NULL;
	result = malloc((s1_s + s2_s + 1) * sizeof(char));
	if (result != NULL)
	{
		while (i < s1_s)
		{
			result[i] = s1[i];
			i++;
		}
		while (i < s1_s + s2_s)
		{
			result[i] = s2[i - s1_s];
			i++;
		}
		result[i] = 0;
	}
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			s1_size;
	size_t			s2_size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = get_str_len(s1);
	s2_size = get_str_len(s2);
	return (do_join(s1_size, s2_size, s1, s2));
}
