
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

// utils
int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	if (!string || string[0] == '\0')
		return (0);
	while (string[i])
		i++;
	return (i);
}

int	length_of_integer(long int x)
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

// puts
char	*putnbr(int x)
{
	int		length;
	char	*convert_return;
	char	*min;

	length = 0;
	if (x == INT_MIN)
	{
		convert_return = malloc(sizeof(char) * 12);
		min = "-2147483648";
		while (*min)
			convert_return[length++] = *(min++);
		convert_return[length] = '\0';
		return (convert_return);
	}
	length = 1 + length_of_integer(x);
	if (x < 0)
		x *= -1;
	else
		length--;
	convert_return = malloc(sizeof(char) * length + 1);
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
	char	*hex;
	char	*convert_return;
	char	*nil;
	hex = "0123456789abcdef";
	length = 0;
	if (!x)
	{
		nil = "(nil)";
		convert_return = malloc(sizeof(char) * 6);
		if (!convert_return)
			return (0);
		while(*nil)
			convert_return[length++] = *(nil++);
		convert_return[length] = '\0';
		return (convert_return);
	}
	length = length_of_hex(x) + 2;
	convert_return = malloc(sizeof(char) * length + 1);
	if(!convert_return)
		return (0);
	convert_return[0] = '0';
	convert_return[1] = 'x';
	convert_return[length--] = '\0';
	if (!x)
		convert_return[2] = '0';
	while(x > 0)
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
	int 	i;

	i = 0;
	if (!string)
	{
		null = "(null)";
		convert_return = malloc(sizeof(char) * 7);
		while(*null)
			convert_return[i++] = *(null++);
		convert_return[i] = '\0';
		return (convert_return);
	}
	else
		convert_return = malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!convert_return)
		return (0);
	while(*string)
		convert_return[i++] = *(string++);
	convert_return[i] = '\0';
	return (convert_return);
}

char	*putchr(int c)
{
	char	*convert_return;

	convert_return = malloc(sizeof(char) + 1);
	convert_return[0] = c;
	convert_return[1] = '\0';
	return(convert_return);
}

char	*putnbr_unsigned(unsigned int x)
{
	int	length;
	char *convert_return;

	length = length_of_integer(x);
	convert_return = malloc(sizeof(char) * length + 1);
	if (!convert_return)
		return 0;
	convert_return[length--] = '\0';
	if (x == 0)
		convert_return[0] = '0';
	while(x > 0)
	{
		convert_return[length--] = (x % 10) + '0';
		x /= 10;
	}
	return (convert_return);
}

// bonus utils
int	is_numeric(char c)
{
	if (c <= '9' && c >= '0') // between 1 and 9 as 0 is for justifying with 0's
		return (1);
	return (0); 
}
