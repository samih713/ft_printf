/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:35:56 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/26 21:50:36 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	is_numeric(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}
