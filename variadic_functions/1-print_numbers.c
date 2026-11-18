#include "variadic_functions.h"
/**
 * print_numbers - prints numbers, followed by a new line
 * @separator: string to be printed between numbers
 * @n: number of integers passed to the function
 * Return: void
 */
void print_numbers(const char *separator, const unsigned int n, ...)
{
	unsigned int i;
	va_list liste;

	va_start(liste, n);

	for (i = 0; i < n; i++)
	{
		printf("%d", va_arg(liste, int));
		if (separator != NULL && i != (n - 1))
			printf("%s", separator);
	}
	va_end(liste);
	printf("\n");
}
