/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:10:03 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/10 13:39:22 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H


#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int	ft_printf(const char *format_string, ...);

// put
int	convert_specifier(char format_specifier, va_list args);
int	ft_itoa(long int x);
int	ft_hex(long x, char upper_lower_case);
int	putptr(unsigned long x);


// utilies
int	ft_strlen(char *string);
int	length_of_integer(unsigned int x);
int	length_of_hex(unsigned long int x);

#endif
