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

// - . 0	(.)			specifies minimum number of digits
//			(-)			left_justify n spaces
//			(0)			right_justify n 0 instead of spaces
//			(default):	right_justify n spaces

// (-) left-justify within the given field width, n[left_justify] right_justify is default
// %-[width] width is mandatory
// % if number store it in variable n, write n - convert_return spaces
// 2 cases for write n spaces
// before value when only a number is given [right_justify]
// after value when (-) + a number given
// 0 [right_justify]

#include "ft_printf.h"

int	is_flag(const char format_string)
{
	char *flags;
	int flag_id;

	flags = "-.0# +"; 
	flag_id = 0;// flag_id 0,1,2
	while (flags[flag_id])
	{
		if (flags[flag_id] == format_string)
			return (flag_id);
		flag_id++;
	}	
	return (-1);
}
// [to-do] justification should be width - length of string;
int	parse(const char **format_string, va_list args) // writes based on is_flags outcome
{
	int print_return;
	t_flag_width *formating_rules;
	int i; //counter

	i = 0;
	print_return = 0;
	formating_rules = init_strct(format_string);
	if (formating_rules->left_justify)
	{
		while(i < formating_rules->width) // maybe should be <=
		{
			print_return += write(1, &formating_rules->padding, 1);
			i++;
		}
		print_return += convert_specifier(**(format_string++), args);
	}
	else if (!formating_rules->left_justify)
	{
		print_return = convert_specifier(**(format_string++), args);
		while(i < formating_rules->width)
		{
			write(1, &formating_rules->padding, 1);
			i++;
		}
	}
	return(print_return);
}
// [to-do] handle precision flag
t_flag_width init_strct(const char **format_string)
{
	t_flag_width *formating_rules;

	formating_rules->width = 0;
	formating_rules->padding = ' ';
	formating_rules->precision = false;
	while(!is_flag(**format_string))
	{
		if (**format_string == '0')
		{
			formating_rules->left_justify = false;
			formating_rules->padding = '0';	
		}
		else if (**format_string == '-')
			formating_rules->left_justify = true;
		else if (**format_string == '#')
			formating_rules->hash = true;
		else if (**format_string == '+')
			formating_rules->show_positive = '+';
		else if (**format_string == ' ')
			formating_rules->show_positive = ' ';
		else if (**format_string == '.')
			formating_rules->precision = true;
		while(is_numeric(*(++(*format_string))))
		{
			if (!formating_rules->precision)
			{
				formating_rules->width *= 10;
				formating_rules->width += **format_string - '0';
			}
			else
			{
				formating_rules->precision_value *= 10;
				formating_rules->precision_value += **format_string - '0';
			}	
		}
		(*format_string)++; // single de-reference to move the pointer
	}
	return(*formating_rules);
}




// 0-# 