/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sps169 <sps169@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:28 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/23 22:11:04 by sps169           ###   ########.fr       */
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

int	ft_isdigit(int c);

int	ft_atoi(const char *str);

#endif