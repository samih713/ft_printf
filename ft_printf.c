/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:52:35 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/11 19:23:38 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
[to-do] learn wtf ar rcs is

[to-do] Bonus
%[flags][width]specifier
 */



#include "ft_printf.h"

static int	convert_specifier(char format_specifier, va_list args);

int	ft_printf(const char *format_string, ...)
{
	va_list args;
	int print_return;

	print_return = 0;
	va_start(args, format_string);
	while(*format_string)
	{
		if (*format_string == '%')
		{
			format_string++;
			// goes here
			print_return += convert_specifier(*format_string++, args); // if its not fs returns 0 and carries on
		}
		else if(!*format_string)
			return(print_return);
		else
		{
			write(1, format_string, 1);
			format_string++;
			print_return++;
		}
	}
	va_end(args);
	return (print_return);
}

static int	convert_specifier(char format_specifier, va_list args)
{
	int convert_return;

	convert_return = 0;
	if(format_specifier == 'c')
		convert_return = putstr(format_specifier, args);
	else if(format_specifier == 's')
		convert_return = putstr(format_specifier, args);
	else if (format_specifier == 'd' || format_specifier == 'i')
		convert_return = putnbr(va_arg(args, int));
	else if (format_specifier == 'u')
		convert_return = putnbr_unsigned(va_arg(args, unsigned int));
	else if (format_specifier == 'x' || format_specifier == 'X')
		convert_return = puthex(va_arg(args,unsigned int), format_specifier);
	else if (format_specifier == 'p')
		convert_return = putptr(va_arg(args, unsigned long));
	else if (format_specifier == '%')
		convert_return = write(1, "%", 1);
	return (convert_return);
}

#include <stdio.h>

int main(void)
{
	printf("%-------4d", 55);
}

