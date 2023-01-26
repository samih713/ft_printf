/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:10:03 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/27 03:30:44 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>

int		ft_printf(const char *format_string, ...);
char	*convert_specifier(char format_specifier, va_list arguments);

// put
char	*putnbr(long int x);
char	*putstr(char *string);
char	*putnbr_unsigned(unsigned int x);
char	*puthex(unsigned int x, char hcase);
char	*putptr(unsigned long x);

// utilies
int		ft_strlen(const char *string);
int		length_of_integer(long int x);
int		length_of_hex(unsigned long int x);

// bonus
typedef int	t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_flag
{
	t_bool	left_justify;
	t_bool	hash;
	t_bool	precision;
	char	*show_positive;
	int		p_value;
	char	padding;
	int		width;
	char	*str;
	int		sl;
	char	sign;
}	t_flag;
// bonus utils
char	*putchr(int c);
int		is_flag_numeric(const char **format_string, t_flag *formating);
void	defaults(t_flag *formating);

int		is_numeric(char c);
t_flag	*init_strct(const char **format_string);
int		parse(const char **format_string, va_list arguments, t_flag *formating);

//error
int		mem_err(void *allocated);

#endif
