/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:13:23 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/10 18:22:33 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *string)
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

int	putnbr(int x)
{
	int		length;
	int		i;
	char	*result;

	if (x == INT_MIN)
		return (write(1, "-2147483648", 11));
	length = 1 + length_of_integer(x);
	if (x < 0)
		x *= -1;
	else
		length--;
	result = (char *)malloc(sizeof(char) * length);
	i = length - 1;
	result[0] = '-';
	if (x == 0)
		result[0] = '0';
	while (x > 0)
	{
		result[i--] = (x % 10) + '0';
		x /= 10;
	}
	write(1, result, length);
	free(result);
	return (length);
}

int	puthex(unsigned int x, char upper_lower_case)
{
	int length;
	int i;
	char *hex;

	if (upper_lower_case == 'x')
		hex = "0123456789abcdef";
	else if (upper_lower_case == 'X')
		hex = "0123456789ABCDEF";
	length = length_of_hex(x);
	char result[length];
	i = length - 1;
	if (x == 0)
		result[0] = '0';
	while(x > 0)
	{
		result[i] = hex[x % 16];
		x /= 16;
		i--;
	}
	write(1, result, length);
	return (length);
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

int	putstr(char format_specifier, va_list args)
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
			convert_return = write(1, "(null)", 6);
		else
			convert_return = write(1, string, ft_strlen(string));
	}
	return (convert_return);
}

int putnbr_unsigned(unsigned int x)
{
	int length;
	int i;

	length = length_of_integer(x);
	i = length - 1;
	char result[length];
	if (x == 0)
		result[0] = '0';
	while(x > 0)
	{
		result[i] = (x % 10) + '0';
		x /= 10;
		i--;
	}
	write(1, result, length);
	return (length);
}
