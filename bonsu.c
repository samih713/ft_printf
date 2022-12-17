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

int	is_flag_numeric(const char format_string, t_flag *formating)
{
	char *flags;
	int flag_id;


	flags = "-.0# +"; 
	flag_id = 0;
    if(is_numeric(format_string))
    {
        if (formating->precision)
        {
            formating->precision_value *= 10;
            formating->precision_value += format_string - '0';
        }
        else
        {
            formating->width *= 10;
            formating->width += format_string - '0';
        }
        return (1);	
    }
	while (flags[flag_id])
	{
		if (flags[flag_id] == format_string)
			return (1);
		flag_id++;
	}	
	return (0);
}

//create the padding string
char	*create_padding(t_flag *formating) 
{
	char	*pad;
	int		size;

	size = 0;
	if (formating->width)
		size = formating->width - formating->string_length; 
	if (formating->hash)									
		size -= 2;
	else if (formating->show_positive) // no show positive with hash ??
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
	{
		pad[size] = formating->padding;
		size--;
	}
	return (pad);
}

t_flag *init_strct(const char **format_string)
{
	t_flag *formating;

    // malloc the correct size of the struct not *struct dumbass
    formating = (t_flag *)malloc(sizeof(t_flag));
    if (!formating)
        return (NULL);  
    // can be shortened if all are initiated to these default values formating =(t_list){false, 0, 1, ...}
    formating->width = 0;
    formating->precision_value = 0;
	formating->padding = ' ';
	formating->precision = false;
    formating->show_positive = 0; // make sure to use as ! if nothing is specified
    formating->left_justify = false;
	formating->hash = 0;
	formating->string = NULL;
	while(is_flag_numeric(**format_string, formating))
	{
		if (!(formating->left_justify) && **format_string == '0')
			formating->padding = '0';	
		else if (formating->padding != '0' && **format_string == '-')
			formating->left_justify = true;
		else if (**format_string == '#')
			formating->hash = true;
		else if (formating->show_positive == 0 && **format_string == '+')
			formating->show_positive = "+";
		else if (formating->show_positive == 0 &&**format_string == ' ')
			formating->show_positive = " ";
		else if (**format_string == '.')
			formating->precision = true;
		(*format_string)++;
	}
	return(formating);
}

int	parse(const char **format_string, va_list args, t_flag *formating) 
{
	char	*result;
	char	*pad;
	int		sign_length; 

	sign_length = 0;
	if (formating->hash)
		sign_length += 2;
	else if (formating->show_positive)
		sign_length += 1;
	formating->string = convert_specifier(**format_string, args);
	formating->string_length = ft_strlen(formating->string);
	pad = create_padding(formating);
	if (formating->width > (formating->string_length + sign_length)) 
		result = (char *)malloc(sizeof(char) * formating->width);
	else
		result = (char *)malloc(sizeof(char) * formating->string_length + sign_length);
	if (!result)
		return 0;
	if (formating->left_justify)
	{
		if (formating->show_positive)
			strncat(result, formating->show_positive , 1);
		else if (formating->hash)
			strncat(result, "0x", 3);
		strncat(result, formating->string, formating->string_length);
		strncat(result, pad, ft_strlen(pad));
	}
	else
	{
		if (formating->hash)
			strncat(result, "0x", 3);
		strncat(result, pad, ft_strlen(pad));
		if (formating->show_positive)
			strncat(result, formating->show_positive , 1);
		strncat(result, formating->string, formating->string_length);
	}
	if (pad)
		free(pad);
	sign_length = ft_strlen(result);
	write(1, result, sign_length);
	if (result)
		free(result);
	return (sign_length);
}
