/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:52:35 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/27 03:45:15 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
[to-do] make a better makefile plx
[to-do] error functions
[to-do] better way to initialize the struct
[to-do] testers
[to-do] readme
 */

#include "ft_printf.h"

char	*convert_specifier(char format_specifier, va_list args);

int	ft_printf(const char *fstr, ...)
{
	va_list	args;
	int		pr;
	t_flag	*f;

	pr = 0;
	va_start(args, fstr);
	while (*fstr)
	{
		if (*fstr == '%')
		{
			fstr++;
			f = init_strct(&fstr);
			pr += parse(&fstr, args, f);
			fstr++;
			free(f);
		}
		else if (!*fstr)
			return (pr);
		else
			pr += write(1, fstr++, 1);
	}
	va_end(args);
	return (pr);
}

char	*convert_specifier(char format_specifier, va_list args)
{
	char	*convert_return;

	convert_return = NULL;
	if (format_specifier == 'c')
		convert_return = putchr(va_arg(args, int));
	else if (format_specifier == 's')
		convert_return = putstr(va_arg(args, char *));
	if (format_specifier == 'd' || format_specifier == 'i')
		convert_return = putnbr(va_arg(args, int));
	else if (format_specifier == 'u')
		convert_return = putnbr_unsigned(va_arg(args, unsigned int));
	else if (format_specifier == 'x' || format_specifier == 'X')
		convert_return = puthex(va_arg(args, unsigned long), format_specifier);
	else if (format_specifier == 'p' || format_specifier == 'P')
		convert_return = putptr(va_arg(args, unsigned long));
	else if (format_specifier == '%')
	{
		convert_return = malloc(2);
		convert_return[0] = '%';
		convert_return[1] = '\0';
	}
	return (convert_return);
}
