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

int	is_flag_numeric(const char **format_string, t_flag *formating)
{
	char *flags;
	int r;


	flags = "-.0# +"; 
	r = 0;
	while (*flags)
	{
		if (*flags == **format_string)
			return (1);
		flags++;
	}	
    while(is_numeric(**format_string))
    {	
		r = 1;
        if (formating->precision)
        {
            formating->precision_value *= 10;
            formating->precision_value += **format_string - '0';
			if(*((*format_string) + 1) && *((*format_string) + 1) == '0')
			{
				formating->precision_value *= 10;
				(*format_string)++;
			}
			else
				(*format_string)++;

        }
        else
        {
            formating->width *= 10;
            formating->width += **format_string - '0';
			if(*((*format_string) + 1) && *((*format_string) + 1) == '0')
			{
				formating->width *= 10;
				(*format_string)++;
			}
			else
				(*format_string)++;
        }
    }
	return (r);	
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
	int		length; 

	length = 0;
	if (formating->hash)
		length += 2;
	else if (formating->show_positive)
		length += 1;
	formating->string = convert_specifier(**format_string, args);
	if (formating->string)
		formating->string_length = ft_strlen(formating->string);
	else
		formating->string_length = 1;
	pad = create_padding(formating);
	if (formating->width > (formating->string_length + length)) 
		//better use calloc when using it to cat as the string might not be empty and you might cat + junk values
		result = (char *)calloc(formating->width + 1 ,sizeof(char)); 
	else
		result = (char *)calloc(formating->string_length + length + 1 ,sizeof(char));
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
	if (formating->string)
		free(formating->string);
	length = ft_strlen(result);
	write(1, result, length);
	if (result)
		free(result);
	return (length);
}
