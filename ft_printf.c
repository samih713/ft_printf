/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:52:35 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/09 22:49:41 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_specifier(char format_specifier, va_list args);

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
			print_return += convert_specifier(*format_string++, args);
		}
		if(!*format_string)
			return(print_return); // to remove the
		write(1, format_string, 1);
		format_string++;
		print_return++;
	}
	return (print_return);
}

int	convert_specifier(char format_specifier, va_list args)
{
	int convert_return;
	char *string;
	int c;

	convert_return = 0;
	if(format_specifier == 'c')
	{
		c = va_arg(args, int);
		convert_return = write(1, &c, 1);
	}
	else if(format_specifier == 's')
	{
		string = (va_arg(args, char *));
		if (!string)
			convert_return = write(1, "(null)", 6); // dumb fix
		else
			convert_return = write(1, string, ft_strlen(string));
	}
	else if (format_specifier == 'd' || format_specifier == 'i' || format_specifier == 'u')
		convert_return = ft_itoa(va_arg(args,long int));
	else if (format_specifier == 'x' || format_specifier == 'X')
		convert_return = ft_hex(va_arg(args, long int), format_specifier);
	else if (format_specifier == 'p')
		convert_return = putptr(va_arg(args, unsigned long));
	else if (format_specifier == '%')
		convert_return = write(1, "%", 1);
	return (convert_return);
}

#include <limits.h>

int main(void)
{
	// int y = ft_printf(" %p %p ", LONG_MIN, LONG_MAX);
	int x = printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
	printf("\n\n\n");
	// printf("pointer LONG_MIN=%p**\n\npointer LONG_MAX=%p**\n\n", LONG_MIN, LONG_MAX);
	printf("ft_printf return is: %d\n\n", x);
	// printf("printf is : %d\nft_printf is : %d\n\n\n", x, y);
}


// " %p %p ", 0, 0
