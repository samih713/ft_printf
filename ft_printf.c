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
[to-do] check for illegal functions (calloc ...etc)
[to-do] Precision
[to-do] fix bonus testers
[to-do] make a better makefile plx
[to-do] variable and function naming, (clear and systematic)
[to-do] readme
 */
#include "ft_printf.h"

char	*convert_specifier(char format_specifier, va_list args);

int	ft_printf(const char *format_string, ...)
{
	va_list	args;
	int		print_return;
	t_flag	*formating;

	print_return = 0;
	va_start(args, format_string);
	while (*format_string)
	{
		if (*format_string == '%')
		{
			format_string++;
			formating = init_strct(&format_string);
			print_return += parse(&format_string, args, formating);
			format_string++;
			free(formating);
		}
		else if (!*format_string)
			return (print_return);
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

char	*convert_specifier(char format_specifier, va_list args) // all should return strings
{
	char	*convert_return;

	convert_return = NULL;
	if(format_specifier == 'c')
		convert_return = putchr(va_arg(args, int));
	else if(format_specifier == 's')
		convert_return = putstr(va_arg(args, char *));
	if (format_specifier == 'd' || format_specifier == 'i')
		convert_return = putnbr(va_arg(args, int));
	else if (format_specifier == 'u')
		convert_return = putnbr_unsigned(va_arg(args, unsigned int));
	else if (format_specifier == 'x' || format_specifier == 'X')
		convert_return = puthex(va_arg(args,unsigned int), format_specifier);
	else if (format_specifier == 'p')
		convert_return = putptr(va_arg(args, unsigned long));
	else if (format_specifier == '%')
	{
		convert_return = malloc(2);
		convert_return[0] = '%';
		convert_return[1] = '\0';
	}
	return (convert_return);
}

/* int main(void)
{
	ft_printf(" % d \n", -1);
	printf(" % d \n", -1);
} */