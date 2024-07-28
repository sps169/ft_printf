/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:17:28 by sperez-s          #+#    #+#             */
/*   Updated: 2024/07/28 16:21:30 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

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

//prints
int	print_arg_char(char character, t_flags flags);

int	print_arg_string(char *string, t_flags flags);

int	print_arg_pointer(void *pointer, t_flags flags);

int	print_arg_decimal(int decimal, t_flags flags);

int	print_arg_unsigned_decimal(unsigned int decimal, t_flags flags);

int	print_arg_hex(unsigned int hex, t_flags flags);

int	print_arg_hex_mayus(unsigned int hex, t_flags flags);

//utils
size_t	ft_strlen(const char *str);

void	ft_putchar(char c);

char	*ft_strchr(const char *s, int c);

int	ft_isdigit(int c);

int	ft_atoi(const char *str);

char	*ft_itoa(int n);

int	ft_putnbr_base(unsigned long num, char *base, size_t base_len);

int	ft_nbr_writer(unsigned long num, char *base, size_t base_len);

char	*ft_utoa_base(unsigned long num, char *base, t_flags flags);

#endif