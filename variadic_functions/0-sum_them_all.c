#include "variadic_functions.h"
/**
 * sum_them_all - sums all its parameters
 * @n: number of parameters
 *
 * Return: the sum of all its parameters, or 0 if n == 0
 */
int sum_them_all(const unsigned int n, ...)
{
	unsigned int i;
	int somme = 0;
	va_list liste;
	if (n == 0)
		return (0);
	va_start(liste, n);
	for (i = 1; i <= n; i++)
		somme = somme + va_arg(liste, int);
	va_end(liste);
	return(somme);
}
