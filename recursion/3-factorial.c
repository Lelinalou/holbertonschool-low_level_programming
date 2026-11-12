#include "main.h"
/**
 * factorial - Returns the factorial of a given number.
 * @n: The number whose factorial is to be calculated.
 * Description: This function calculates the factorial of a given number
 * using recursion. It multiplies the number by the factorial of the number
 * decremented by 1 until it reaches the base case of 0 or 1.
 * Return: The factorial of the number, or -1 if the number is negative.
 */
int factorial(int n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (1);
	return (n * factorial(n - 1));
}
