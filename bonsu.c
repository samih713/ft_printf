/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonsu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:22:57 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/27 03:29:35 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	left_justify(t_flag *f, const char **fstr, char *pad, int pr);
static int	right_justify(t_flag *f, const char **fstr, char *pad, int pr);
static char	*create_padding(t_flag *f);

t_flag	*init_strct(const char **fstr)
{
	t_flag	*f;

	f = malloc(sizeof(t_flag));
	mem_err(f);
	defaults(f);
	while (is_flag_numeric(fstr, f))
	{
		if (!(f->left_justify) && **fstr == '0')
			f->padding = '0';
		else if (f->padding != '0' && **fstr == '-')
			f->left_justify = TRUE;
		else if (**fstr == '#')
			f->hash = TRUE;
		else if (f->show_positive == 0 && **fstr == '+')
			f->show_positive = "+";
		else if (f->show_positive == 0 && **fstr == ' ')
			f->show_positive = " ";
		else if (**fstr == '.')
			f->precision = TRUE;
		(*fstr)++;
	}
	return (f);
}

int	parse(const char **fstr, va_list args, t_flag *f)
{
	int		pr;
	char	*pad;

	pr = 0;
	f->str = convert_specifier(**fstr, args);
	if (**fstr == 'c' || **fstr == 's' || f->str[0] == '-')
		f->show_positive = 0;
	if (!f->str[0] && **fstr == 'c')
		f->sl = 1;
	else
		f->sl = ft_strlen(f->str);
	pad = create_padding(f);
	if (f->left_justify)
		pr = left_justify(f, fstr, pad, pr);
	else
		pr = right_justify(f, fstr, pad, pr);
	if (pad)
		free(pad);
	if (f->str)
		free(f->str);
	return (pr);
}

static int	left_justify(t_flag *f, const char **fstr, char *pad, int pr)
{
	if (f->show_positive && (**fstr != 'x' || **fstr != 'X'))
		pr += write(1, f->show_positive, 1);
	if (f->hash && **fstr == 'x')
		pr += write(1, "0x", 2);
	else if (f->hash && **fstr == 'X')
		pr += write(1, "0X", 2);
	if (**fstr == 's' && f->precision)
		pr += write(1, f->str, f->p_value);
	else if (**fstr != 's')
	{
		f->p_value = f->p_value - f->sl;
		while ((f->p_value)-- > 0)
			pr += write(1, "0", 1);
		pr += write(1, f->str, f->sl);
	}
	else
		pr += write(1, f->str, f->sl);
	pr += write(1, pad, ft_strlen(pad));
	return (pr);
}

static int	right_justify(t_flag *f, const char **fstr, char *pad, int pr)
{
	if ((f->str[0] == '-' && **fstr != 's'))
	{
		pr += write(1, f->str, 1);
		f->sl--;
	}
	if (f->hash && **fstr == 'x' && f->str[0] != '0')
		pr += write(1, "0x", 2);
	else if (f->hash && **fstr == 'X' && f->str[0] != '0')
		pr += write(1, "0X", 2);
	pr += write(1, pad, ft_strlen(pad));
	if (f->show_positive && !f->hash)
		pr += write(1, f->show_positive, 1);
	if (**fstr == 's' && f->precision && (f->p_value < f->sl))
		pr += write(1, f->str
				+ (f->str[0] == '-' && **fstr != 's'), f->p_value);
	else if (**fstr != 's')
	{
		f->p_value = f->p_value - f->sl;
		while ((f->p_value)-- > 0)
			pr += write(1, "0", 1);
		pr += write(1, f->str + (f->str[0] == '-' && **fstr != 's'), f->sl);
	}
	else
		pr += write(1, f->str, f->sl);
	return (pr);
}

static char	*create_padding(t_flag *f)
{
	char	*pad;
	int		size;

	size = 0;
	if (f->width)
		size = f->width - f->sl;
	if (f->hash)
		size -= 2;
	else if (f->show_positive)
		size -= 1;
	if (size > 0)
	{
		pad = malloc(sizeof(char) * size + 1);
		mem_err(pad);
	}
	else
	{
		pad = malloc(1);
		pad[0] = '\0';
		return (pad);
	}
	pad[size--] = '\0';
	while (size >= 0)
		pad[size--] = f->padding;
	return (pad);
}
