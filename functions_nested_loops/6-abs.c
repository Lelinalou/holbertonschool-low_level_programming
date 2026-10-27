#include "main.h"
/**
 * _abs - computes the absolute value of an integer
 * @n: the integer to process
 *
 * Return: n if n is positive or zero, -n if n is negative
 */
int _abs(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}
