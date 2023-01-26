/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonsu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:22:57 by sabdelra          #+#    #+#             */
/*   Updated: 2023/01/26 22:21:37 by sabdelra         ###   ########.fr       */
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
	if (!f)
		return (NULL);
	defaults(f);
	while (is_flag_numeric(fstr, f))
	{
		if (!(f->left_justify) && **fstr == '0')
			f->padding = '0';
		else if (f->padding != '0' && **fstr == '-')
			f->left_justify = true;
		else if (**fstr == '#')
			f->hash = true;
		else if (f->show_positive == 0 && **fstr == '+')
			f->show_positive = "+";
		else if (f->show_positive == 0 && **fstr == ' ')
			f->show_positive = " ";
		else if (**fstr == '.')
			f->precision = true;
		(*fstr)++;
	}
	return (f);
}

int	parse(const char **fstr, va_list args, t_flag *f)
{
	int		pr;
	char	*pad;

	pr = 0;
	f->string = convert_specifier(**fstr, args);
	if (**fstr == 'c' || **fstr == 's' || f->string[0] == '-')
		f->show_positive = 0;
	if (!f->string[0] && **fstr == 'c')
		f->string_length = 1;
	else
		f->string_length = ft_strlen(f->string);
	pad = create_padding(f);
	if (f->left_justify)
		pr = left_justify(f, fstr, pad, pr);
	else
		pr = right_justify(f, fstr, pad, pr);
	if (pad)
		free(pad);
	if (f->string)
		free(f->string);
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
		pr += write(1, f->string, f->p_value);
	else if (**fstr != 's')
	{
		f->p_value = f->p_value - f->string_length;
		while ((f->p_value)-- > 0)
			pr += write(1, "0", 1);
		pr += write(1, f->string, f->string_length);
	}
	else
		pr += write(1, f->string, f->string_length);
	pr += write(1, pad, ft_strlen(pad));
	return (pr);
}

static int	right_justify(t_flag *f, const char **fstr, char *pad, int pr)
{
	int	sign;

	sign = (f->string[0] == '-' && **fstr != 's');
	if (sign)
	{
		pr += write(1, f->string, 1);
		f->string_length--;
	}
	if (f->hash && **fstr == 'x' && f->string[0] != '0')
		pr += write(1, "0x", 2);
	else if (f->hash && **fstr == 'X' && f->string[0] != '0')
		pr += write(1, "0X", 2);
	pr += write(1, pad, ft_strlen(pad));
	if (f->show_positive && !f->hash)
		pr += write(1, f->show_positive, 1);
	if (**fstr == 's' && f->precision && (f->p_value < f->string_length))
		pr += write(1, f->string + sign, f->p_value);
	else if (**fstr != 's')
	{
		f->p_value = f->p_value - f->string_length;
		while ((f->p_value)-- > 0)
			pr += write(1, "0", 1);
		pr += write(1, f->string + sign, f->string_length);
	}
	else
		pr += write(1, f->string, f->string_length);
	return (pr);
}

static char	*create_padding(t_flag *f)
{
	char	*pad;
	int		size;

	size = 0;
	if (f->width)
		size = f->width - f->string_length;
	if (f->hash)
		size -= 2;
	else if (f->show_positive)
		size -= 1;
	if (size > 0)
	{
		pad = malloc(sizeof(char) * size + 1);
		if (!pad)
			return (0);
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
