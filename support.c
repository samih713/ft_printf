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
	if (!string)
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
	int		i; // remove i no need for it since not returning length anymore
	char	*result;

	if (x == INT_MIN)
	{
		result = (char *)malloc(sizeof(char) * 12);
		result = "-2147483648";
		return (result);
	}
	length = 1 + length_of_integer(x);
	if (x < 0)
		x *= -1;
	else
		length--;
	result = (char *)malloc(sizeof(char) * length + 1);
	i = length - 1;
	result[length] = '\0';
	result[0] = '-';
	if (x == 0)
		result[0] = '0';
	while (x > 0)
	{
		result[i--] = (x % 10) + '0';
		x /= 10;
	}
	return (result); // free after it gets copied
}

char	*puthex(unsigned int x, char upper_lower_case)
{
	int length;
	int i;
	char *hex;
	char *result;

	if (upper_lower_case == 'x')
		hex = "0123456789abcdef";
	else if (upper_lower_case == 'X')
		hex = "0123456789ABCDEF";
	length = length_of_hex(x);
	result = malloc(sizeof(char) * length + 1);
	if (!result)
		return 0;
	result[length] = '\0';
	i = length - 1;
	if (x == 0)
		result[0] = '0';
	while(x > 0)
	{
		result[i] = hex[x % 16];
		x /= 16;
		i--;
	}
	return (result);
}

int	putptr(unsigned long x)
{
	int length;
	int i;
	char *hex;

	length = 0;
	hex = "0123456789abcdef";
	length += length_of_hex(x) + 2;
	char result[length];
	result[0] = '0';
	result[1] = 'x';
	if (!x)
		result[2] = '0';
	i = length - 1;
	while(x > 0)
	{
		result[i] = hex[x % 16];
		x /= 16;
		i--;
	}
	write(1, result, length);
	return (length);
}

char	*putstr(char format_specifier, va_list args)
{
	int convert_return;
	char *string;
	int c;

	convert_return = 0;
	if(format_specifier == 'c')
	{
		string = malloc(sizeof(char) + 1);
		string[0] = (char)va_arg(args, int);
		string[1] = '\0';
	}
	else if(format_specifier == 's')
	{
		string = (va_arg(args, char *));
	}
	return (string);
}

char	*putnbr_unsigned(unsigned int x)
{
	int	length;
	int	i;
	char *result;

	length = length_of_integer(x);
	i = length - 1;
	result = malloc(sizeof(char) * length + 1);
	if (!result)
		return 0;
	result[length] = '\0';
	if (x == 0)
		result[0] = '0';
	while(x > 0)
	{
		result[i] = (x % 10) + '0';
		x /= 10;
		i--;
	}
	return (result);
}

// bonus utils

int	is_numeric(char c)
{
	if (c <= '9' && c >= '1') // between 1 and 9 as 0 is for justifying with 0's
		return (1);
	return (0); 
}
