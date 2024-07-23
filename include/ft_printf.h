/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:28 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/23 20:20:52 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags {
	int		plus;
	int		zero;
	int		minus;
	int		hash;
	int		blank;
	int		min_width;
	int		period;
	int		precision;
	char	type;
} t_flags;

int	ft_printf(char const *format, ...);

//utils
size_t	ft_strlen(const char *str);

void	ft_putchar(char c);

char	*ft_strchr(const char *s, int c);

#endif