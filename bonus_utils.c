/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:35:59 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/27 22:33:29 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*putchr(int c)
{
	char	*convert_return;

	convert_return = malloc(sizeof(char) + 1);
	mem_err(convert_return);
	convert_return[0] = c;
	convert_return[1] = '\0';
	return (convert_return);
}

int	is_flag_numeric(const char **fstr, t_flag *f)
{
	char	*flags;
	int		r;

	flags = "-.0# +";
	r = 0;
	while (*flags && (!f->p_value && !f->width))
	{
		if (*flags++ == **fstr)
			return (1);
	}
	if (is_numeric(**fstr))
	{
		r = 1;
		if (f->precision)
		{
			f->p_value *= 10;
			f->p_value += **fstr - '0';
		}
		else
		{
			f->width *= 10;
			f->width += **fstr - '0';
		}
	}
	return (r);
}

void	defaults(t_flag *f)
{
	f->width = 0;
	f->padding = ' ';
	f->p_value = 0;
	f->precision = FALSE;
	f->show_positive = 0;
	f->left_justify = FALSE;
	f->hash = 0;
	f->str = "(NULL)";
}
