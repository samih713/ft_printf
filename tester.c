#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

typedef struct s_flag
{
	bool	left_justify;
	bool	hash;
	bool	precision;
	char	show_positive;
	int		precision_value;
	char	padding;
	int		width;
	//char	*string;
}	t_flag;

int	is_numeric(char c)
{
	if (c <= '9' && c >= '1') // between 1 and 9 as 0 is for justifying with 0's
		return (1);
	return (0); 
}

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


int main(void)
{
    t_flag *flag_width;
    const char *format_string = "+-08.5d";

    flag_width = init_strct(&format_string);
    printf("left_justify: %d\n", flag_width->left_justify)	;
	printf("hash:         %d\n", flag_width->hash)	;
	printf("precision:    %d\n", flag_width->precision)	;
    printf("showpositive: %c\n", flag_width->show_positive);
    printf("pre_value:    %d\n", flag_width->precision_value);
    printf("padding:      %c\n", flag_width->padding);
    printf("width         %d\n", flag_width->width);
}