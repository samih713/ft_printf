/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:10:03 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/10 18:23:04 by sabdelra         ###   ########.fr       */
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

#endif
