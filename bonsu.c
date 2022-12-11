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

int	is_flag(char **format_string) // double pointer to move the actual pointer also checks for width
{
	char *flags;
	int width;

	width =0;
	flags = "-.0";
	while (*flags)
	{
		if (*flags == **format_string)
		{
			*format_string++;
			return (1); // return -1 if the character is a flag
		}
		while (is_numeric(**format_string))
		{
			width += **format_string - '0';
			*format_string++; // go next character
		}
		flags++;
	}
	if (width)
		return(width * -1); // to distinguish between width and regular flag (1)
	return (0); // return 0 when the character isn't a flag
}

void	parse(char **format_string) // writes based on is_flags outcome
{
	int precision; // count of precision .
	int justification; //count of justification
	t_flag_width prs;

	// by default left_justify = false, zero = false, and width = 0
	prs = (t_flag_width){false, false, 0};
	if (is_flag(**format_string) == false)
		return ; // don't do anything if its not a flag or
	else if (is_flag == 1)
	{
		if (**format_string == '-')
			prs.left_justify = true;
		else if (**format_string == '0')
			prs.zero = true;
		else
			
	}
}

-04.3

if a flag is true once ignore reminging instances of the same flag till a specifier is encounterd
// how to write it
if (-) left_justify = True, default left_justify = false;
if (0) zero = true write '0', default false write ' ';
//
if (.) digits = true use no. of digits, default false dont use it

any number is also considered a flag width=true, false

