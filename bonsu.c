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

int	is_flag_numeric(const char format_string, t_flag *formating) // make it check for numeric here and set accordingly precision or width
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

char	*create_padding(t_flag *formating) //create the padding string
{
	char	*pad;
	int		size;

	size = 0;
	if (formating->width)
		size = formating->width - formating->string_length; // to determine min width
	if (formating->hash)									// space for 0x
		size -= 2;
	else if (formating->show_positive) // no show positive with hash ??
		size -= 1;
	if (size > 0)
	{
		pad = (char *)malloc(sizeof(char) * size + 1); // + 1 to place a null
		if (!pad)
			return (0);
	}
	else
		return (NULL);
	pad[size] = '\0';
	while(--size > 0)
		pad[size] = formating->padding;
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
    formating->show_positive = '\0'; // make sure to use as ! if nothing is specified
    formating->left_justify = false;
	while(is_flag_numeric(**format_string, formating))
	{
		if (!(formating->left_justify) && **format_string == '0')
			formating->padding = '0';	
		else if (formating->padding != '0' && **format_string == '-')
			formating->left_justify = true;
		else if (**format_string == '#')
			formating->hash = true;
		else if (**format_string == '+')
			formating->show_positive = '+';
		else if (**format_string == ' ')
			formating->show_positive = ' ';
		else if (**format_string == '.')
			formating->precision = true;
		(*format_string)++;
	}
	return(formating);
}

int	parse(const char **format_string, va_list args) // fix the parsing to make string in the struct
{
	t_flag		*formating;
	char		*result;
	const char	*padding;
	size_t		sign_length; 
	// needs to be freed
	sign_length = 0;
	if (formating->hash)
		sign_length += 2;
	if (formating->show_positive)
		sign_length += 1;
	//result_length = 0;
	formating = init_strct(format_string); // after struct is initialized, ptr is at specifier hopefully
	formating->string = convert_specifier(**format_string, args);
	formating->string_length = ft_strlen(formating->string);
	padding = create_padding(formating);
	if (formating->width > (formating->string_length + sign_length)) // maybe just width
		result = (char *)malloc(sizeof(char) * formating->width);
	else
		result = (char *)malloc(sizeof(char) * formating->string_length + sign_length);
	if (!result)
		return 0;
	if (formating->left_justify)
	{
		strncat(result, padding, ft_strlen(padding));
		if (formating->show_positive)
			strncat(result, formating->show_positive , 1);
		if (formating->hash)
			strncat(result, "0x", 2);
		strncat(result, formating->string, formating->string_length);
	}
	else
	{
		strncat(result, formating->string, formating->string_length);
		if (formating->show_positive)
			strncat(result, formating->show_positive , 1);
		if (formating->hash)
			strncat(result, "0x", 2);
		strncat(result, padding, ft_strlen(padding));
	}
	write(1, result, ft_strlen(result));
	return (ft_strlen(result));
}


	// //bool	left_justify;
	// //bool	hash;
	// bool	precision;
	// //char	show_positive;
	// int		precision_value;
	// //char	padding;
	// //int		width;
	// char	*string;
	// int		string_length;

	// [list to free]
	// convert_specifier result
	// formating struct
	// padding
	// free result after writing it