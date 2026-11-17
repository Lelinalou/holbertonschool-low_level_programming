#include "main.h"
/**
 * sum_them_all - sums all its parameters
 * @n: number of parameters
 *
 * Return: the sum of all its parameters, or 0 if n == 0
 */
int sum_them_all(const unsigned int n, ...)
{
	if (n == 0)
		return (0);