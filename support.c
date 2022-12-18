
 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:13:23 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/11 17:42:52 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	if (string[0] == '\0')
		return (0);
	while (string[i])
		i++;
	return (i);
}

int	length_of_integer(int x)
{
	if (x < 0)
		x *= -1;
	if (x / 10 == 0)
		return (1);
	else
		return (1 + length_of_integer(x / 10));
}

int	length_of_hex(unsigned long int x)
{
	if (x / 16 == 0)
		return (1);
	else
		return (1 + length_of_hex(x / 16));
}

char	*putnbr(int x)
{
	int		length;
	char	*convert_return;

	if (x == INT_MIN)
	{
		convert_return = (char *)malloc(sizeof(char) * 12);
		convert_return = "-2147483648";
		return (convert_return);
	}
	length = 1 + length_of_integer(x);
	if (x < 0)
		x *= -1;
	else
		length--;
	convert_return = (char *)malloc(sizeof(char) * length + 1);
	convert_return[length--] = '\0';
	convert_return[0] = '-';
	if (x == 0)
		convert_return[0] = '0';
	while (x > 0)
	{
		convert_return[length--] = (x % 10) + '0';
		x /= 10;
	}
	return (convert_return);
}

char	*puthex(unsigned int x, char upper_lower_case)
{
	int length;
	int i;
	char *hex;
	char *convert_return;

	if (upper_lower_case == 'x')
		hex = "0123456789abcdef";
	else if (upper_lower_case == 'X')
		hex = "0123456789ABCDEF";
	length = length_of_hex(x);
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return (0);
	convert_return[length] = '\0';
	i = length - 1;
	if (x == 0)
		convert_return[0] = '0';
	while(x > 0)
	{
		convert_return[i] = hex[x % 16];
		x /= 16;
		i--;
	}
	return (convert_return);
}

char	*putptr(unsigned long x)
{
	int		length;
	int		i;
	char	*hex;
	char	*convert_return;

	hex = "0123456789abcdef";
	length = length_of_hex(x) + 2;
	convert_return = malloc(sizeof(char) * length + 1);
	if(!convert_return)
		return (0);
	convert_return[0] = '0';
	convert_return[1] = 'x';
	convert_return[length] = '\0';
	if (!x)
		convert_return[2] = '0';
	i = length - 1;
	while(x > 0)
	{
		convert_return[i] = hex[x % 16];
		x /= 16;
		i--;
	}
	return (convert_return);
}

char	*putstr(char format_specifier, va_list args)
{
	char *convert_return;

	if(format_specifier == 'c')
	{
		convert_return = malloc(sizeof(char) + 1);
		convert_return[0] = va_arg(args, int);
		convert_return[1] = '\0';
	}
	else if(format_specifier == 's')
	{
		convert_return = (va_arg(args, char *));
	}
	return (convert_return);
}

char	*putnbr_unsigned(unsigned int x)
{
	int	length;
	int	i;
	char *convert_return;

	length = length_of_integer(x);
	i = length - 1;
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return 0;
	convert_return[length] = '\0';
	if (x == 0)
		convert_return[0] = '0';
	while(x > 0)
	{
		convert_return[i] = (x % 10) + '0';
		x /= 10;
		i--;
	}
	return (convert_return);
}

// bonus utils

int	is_numeric(char c)
{
	if (c <= '9' && c >= '1') // between 1 and 9 as 0 is for justifying with 0's
		return (1);
	return (0); 
}
