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

int	ft_printf(const char *format_string, ...);

// put
int	putnbr(int x);
int	puthex(unsigned int x, char upper_lower_case);
int	putptr(unsigned long x);
int putnbr_unsigned(unsigned int);
int	putstr(char format_specifier, va_list args);

// utilies
int	ft_strlen(char *string);
int	length_of_integer(int x);
int	length_of_hex(unsigned long int x);

// bonus
typedef int bool;
#define true 1
#define false 0

typedef struct s_flag_width
{
	bool	left_justify;
	bool	zero;
	//int		digits;
}	t_flag_width;

int	is_numeric(char c);




#endif
