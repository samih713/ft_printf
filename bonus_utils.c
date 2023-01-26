/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:35:59 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/26 21:30:15 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*putchr(int c)
{
	char	*convert_return;

	convert_return = malloc(sizeof(char) + 1);
	convert_return[0] = c;
	convert_return[1] = '\0';
	return (convert_return);
}

int	is_flag_numeric(const char **fstr, t_flag *formating)
{
	char	*flags;
	int		r;

	flags = "-.0# +";
	r = 0;
	while (*flags && (!formating->p_value && !formating->width))
	{
		if (*flags++ == **fstr)
			return (1);
	}
	if (is_numeric(**fstr))
	{
		r = 1;
		if (formating->precision)
		{
			formating->p_value *= 10;
			formating->p_value += **fstr - '0';
		}
		else
		{
			formating->width *= 10;
			formating->width += **fstr - '0';
		}
	}
	return (r);
}

void	defaults(t_flag *f)
{
	f->width = 0;
	f->padding = ' ';
	f->p_value = 0;
	f->precision = false;
	f->show_positive = 0;
	f->left_justify = false;
	f->hash = 0;
	f->str = "(NULL)";
}

