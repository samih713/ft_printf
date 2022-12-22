/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:10:03 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/11 19:45:23 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H


#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

int		ft_printf(const char *format_string, ...);
char	*convert_specifier(char format_specifier, va_list args);

// put
char	*putnbr(int x);
char	*putstr(char *string);
char	*putchr(int c);
char	*putnbr_unsigned(unsigned int x);
char	*puthex(unsigned int x, char upper_lower_case);
char	*putptr(unsigned long x);

// utilies
int		ft_strlen(const char *string);
int		length_of_integer(long int x);
int		length_of_hex(unsigned long int x);

// bonus
typedef int BOOL;
#define true 1
#define false 0

typedef struct s_flag
{
	BOOL	left_justify;
	BOOL	hash;
	BOOL	precision;
	char	*show_positive;
	int		precision_value;
	char	padding;
	int		width;
	char	*string;
	int		string_length;
	char	sign;
}	t_flag;


int	is_numeric(char c);
int	parse(const char **format_string, va_list args, t_flag *formating);
int	is_flag_numeric(const char **format_string, t_flag *formating);
t_flag *init_strct(const char **format_string);

#endif
