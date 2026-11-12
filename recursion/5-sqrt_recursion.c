#include "main.h"
/**
 * _sqrt_recursion - Returns the natural square root of a number.
 * @n: The number whose square root is to be calculated.
 * Description: This function calculates the natural square root of a number
 * using recursion. It checks if the square of the current guess is equal to n,
 * and if not, it increments the guess and checks again until it finds the square root
 * or determines that n does not have a natural square root.
 * Return: The natural square root of the number, or -1 if the number does not
 * have a natural square root.
 */
int helper(int n, int guess)
{
	if (guess * guess > n)
		return (-1);
	if (guess * guess == n)
		return (guess);
	if (guess * guess < n)
		return (helper(n, guess + 1));
	return(0);
}

int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	return(helper(n, 0));
}
