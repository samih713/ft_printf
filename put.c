/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:14:50 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/26 21:50:15 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*putnbr(long int x)
{
	int		length;
	char	*convert_return;

	length = 1 + length_of_integer(x);
	if (x < 0)
		x *= -1;
	else
		length--;
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return (0);
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

char	*puthex(unsigned int x, char hcase)
{
	int		length;
	int		i;
	char	*hex;
	char	*convert_return;

	hex = "0123456789abcdef";
	if (hcase == 'X')
		hex = "0123456789ABCDEF";
	length = length_of_hex(x);
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return (0);
	convert_return[length] = '\0';
	i = length - 1;
	if (x == 0)
		convert_return[0] = '0';
	while (x > 0)
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
	char	*hex;
	char	*convert_return;

	hex = "0123456789abcdef";
	length = 0;
	length = length_of_hex(x) + 2;
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return (0);
	convert_return[0] = '0';
	convert_return[1] = 'x';
	convert_return[length--] = '\0';
	if (!x)
		convert_return[2] = '0';
	while (x > 0)
	{
		convert_return[length--] = hex[x % 16];
		x /= 16;
	}
	return (convert_return);
}

char	*putstr(char *string)
{
	char	*convert_return;
	char	*null;
	int		i;

	i = 0;
	if (!string)
	{
		null = "(null)";
		convert_return = malloc(sizeof(char) * 7);
		while (*null)
			convert_return[i++] = *(null++);
		convert_return[i] = '\0';
		return (convert_return);
	}
	else
		convert_return = malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!convert_return)
		return (0);
	while (*string)
		convert_return[i++] = *(string++);
	convert_return[i] = '\0';
	return (convert_return);
}

char	*putnbr_unsigned(unsigned int x)
{
	int		length;
	char	*convert_return;

	length = length_of_integer(x);
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return (0);
	convert_return[length--] = '\0';
	if (x == 0)
		convert_return[0] = '0';
	while (x > 0)
	{
		convert_return[length--] = (x % 10) + '0';
		x /= 10;
	}
	return (convert_return);
}
