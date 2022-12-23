/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonsu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:08:48 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/11 20:22:03 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

static int	left_justify(t_flag *formating, const char **format_string, char *pad, int print_return);
static int	right_justify(t_flag *formating, const char **format_string, char *pad, int print_return);
static char	*create_padding(t_flag *formating);
static int	is_flag_numeric(const char **format_string, t_flag *formating);

t_flag *init_strct(const char **format_string)
{
	t_flag *formating;

    formating = (t_flag *)malloc(sizeof(t_flag));
    if (!formating)
        return (NULL);
    formating->width = 0;
	formating->padding = ' ';
    formating->precision_value = 0;
	formating->precision = false;
    formating->show_positive = 0;
    formating->left_justify = false;
	formating->hash = 0;
	formating->string = "(NULL)";
	while(is_flag_numeric(format_string, formating))
	{
		if (!(formating->left_justify) && **format_string == '0')
			formating->padding = '0';	
		else if (formating->padding != '0' && **format_string == '-')
			formating->left_justify = true;
		else if (**format_string == '#')
			formating->hash = true;
		else if (formating->show_positive == 0 && **format_string == '+')
			formating->show_positive = "+";
		else if (formating->show_positive == 0 && **format_string == ' ')
			formating->show_positive = " ";
		else if (**format_string == '.')
			formating->precision = true;
		(*format_string)++;
	}
	return(formating);
}

int	parse(const char **format_string, va_list args, t_flag *formating) 
{
	int		print_return; 
	char	*pad;

	print_return = 0;
	formating->string = convert_specifier(**format_string, args);
	if (**format_string == 'c' || **format_string == 's' || formating->string[0] == '-') 
		formating->show_positive = 0;
	if (!formating->string[0] && **format_string == 'c')
		formating->string_length = 1;
	else
		formating->string_length = ft_strlen(formating->string);
	pad = create_padding(formating);
	if (formating->left_justify)
		print_return = left_justify(formating, format_string, pad, print_return);
	else
		print_return = right_justify(formating, format_string, pad, print_return);
	if (pad)
		free(pad);
	free(formating->string);
	return (print_return);
}

static int	left_justify(t_flag *formating, const char **format_string, char *pad, int print_return)
{
	if (formating->show_positive && (**format_string != 'x' || **format_string != 'X'))
			print_return += write(1, formating->show_positive , 1);
	if (formating->hash && **format_string == 'x')
		print_return += write(1, "0x", 2);
	else if (formating->hash && **format_string == 'X')
		print_return += write(1, "0X", 2);
	if (**format_string == 's' && formating->precision)
		print_return += write(1, formating->string, formating->precision_value); 
	else if (**format_string != 's')
	{
		formating->precision_value = formating->precision_value - formating->string_length;
		while ((formating->precision_value)-- > 0)
			print_return += write(1, "0", 1);
		print_return += write(1, formating->string, formating->string_length); 
	}
	else
		print_return += write(1, formating->string, formating->string_length); 
	print_return += write(1, pad, ft_strlen(pad));
	return (print_return);
}

static int	right_justify(t_flag *formating, const char **format_string, char *pad, int print_return)
{
	int		sign;

	sign = 0;
	if(formating->string[0] == '-' && **format_string != 's')
	{
		print_return += write(1, &formating->string[0], 1);
		sign++;
		formating->string_length--;
	}
	if (formating->hash && **format_string == 'x' && formating->string[0] != '0')
		print_return += write(1, "0x", 2);
	else if (formating->hash && **format_string == 'X' && formating->string[0] != '0')
		print_return += write(1, "0X", 2);
	print_return += write(1, pad, ft_strlen(pad));
	if (formating->show_positive && !formating->hash)
		print_return += write(1, formating->show_positive , 1);
	if (**format_string == 's' && formating->precision && (formating->precision_value < formating->string_length))
		print_return += write(1, formating->string + sign, formating->precision_value);
	else if (**format_string != 's')
	{
		formating->precision_value = formating->precision_value - formating->string_length;
		while ((formating->precision_value)-- > 0)
			print_return += write(1, "0", 1);
		print_return += write(1, formating->string + sign, formating->string_length); 	
	}
	else
		print_return += write(1, formating->string, formating->string_length);
	return (print_return);
}

static char	*create_padding(t_flag *formating)
{
	char	*pad;
	int		size;

	size = 0;
	if (formating->width)
		size = formating->width - formating->string_length; 
	if (formating->hash)									
		size -= 2;
	else if (formating->show_positive)
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
	while(size >= 0)
		pad[size--] = formating->padding;
	return (pad);
}

static int	is_flag_numeric(const char **format_string, t_flag *formating)
{
	char *flags;
	int r;

	flags = "-.0# +"; 
	r = 0;
	while (*flags && (!formating->precision_value && !formating->width))
	{
		if (*flags == **format_string)
			return (1);
		flags++;
	}	
    if(is_numeric(**format_string))
    {	
		r = 1;
        if (formating->precision)
        {
            formating->precision_value *= 10;
            formating->precision_value += **format_string - '0';
        }
        else
        {
            formating->width *= 10;
            formating->width += **format_string - '0';
        }
    }
	return (r);	
}