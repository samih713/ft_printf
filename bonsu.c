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
	return 0;
}


