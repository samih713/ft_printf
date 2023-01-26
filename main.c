#include <stdarg.h>

int ft_printf(const char *format_string, ...)
{
	va_list arguments;
	int pr;

	va_start(arguments, format_string);
	while(*format_string)
	{
		if (*format_string == '%')
		{
			format_string++;
			convert_specifier(*format_string, arguments)
				char *name = va_arg(arguments, char *);
				pr += write(1, name, ft_strlen(name));
		}
		
	}
}




