#include "variadic_functions.h"
/**
 * print_strings - prints strings, followed by a new line
 * @separator: string to be printed between strings
 * @n: number of strings passed to the function
 * Return: void
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
	unsigned int i;
	va_list liste;
	char *p;

	va_start(liste, n);

	for (i = 0; i < n; i++)
	{
		p = va_arg(liste, char *);
		if (p == NULL)
			printf("(nil)");
		else
			printf("%s", p);
		if (separator != NULL && i != (n - 1))
			printf("%s", separator);
	}
	va_end(liste);
	printf("\n");
}
