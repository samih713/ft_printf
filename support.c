/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:13:23 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/10 13:40:18 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *string)
{
	int i;

	i = 0;
	if(!string)
		return (0);
	while(string[i])
		i++;
	return (i);
}

int	length_of_integer(unsigned int x)
{
	if(x/10 == 0)
		return (1);
	else
		return (1 + length_of_integer(x/10));
}

int	length_of_hex(unsigned long int x)
{
	if(x/16 == 0)
		return (1);
	else
		return (1 + length_of_hex(x/16));
}

int	ft_itoa(long int x)
{
	int length;
	int i;

	length = 0;
	if (!x)
		return 0;
	if (x < 0)
	{
		x = -x;
		length = 1;
	}
	length += length_of_integer(x);
	i = length - 1;
	char result[length];
	result[0] = '-';
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

int	ft_hex(long x, char upper_lower_case)
{
	int length;
	int i;
	char *hex;

	if (!x)
		return 0;
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
	if (!x)
		return (write(1, "(null)", 6));
	hex = "0123456789abcdef";
	length += length_of_hex(x) + 2;
	char result[length];
	result[0] = '0';
	result[1] = 'x';
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

