#include "variadic_functions.h"
/**
 * print_all - prints anything
 * @format: list of types of arguments passed to the function
 * Return: void
 */
void print_all(const char * const format, ...)
{
	va_list liste;
	int j = 0;
	char *p;
	char *separator = "";

	va_start(liste, format);

	while (format != NULL && format[j] != '\0')
	{
		switch (format[j])
		{
			case 'c':
				printf("%s%c", separator, va_arg(liste, int));
				separator = ", ";
				break;
			case 'i':
				printf("%s%d", separator, va_arg(liste, int));
				separator = ", ";
				break;
			case 'f':
				printf("%s%f", separator, va_arg(liste, double));
				separator = ", ";
				break;
			case 's':
			{
				p = va_arg(liste, char *);
				if (p == NULL)
					p = "(nil)";
				printf("%s%s", separator, p);
				separator = ", ";
				break;
			}
			default:
				break;
		}
		j++;

		}
		va_end(liste);
		printf("\n");
}
