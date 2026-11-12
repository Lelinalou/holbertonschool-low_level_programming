#include "main.h"
/**
 * helper - A helper function to find the square root of a number.
 * @n: The number whose square root is to be calculated.
 * @guess: The current guess for the square root.
 * Description: This function uses recursion to find the square root of a
 * given number by checking if the square of the current guess is equal to,
 * less than, or greater than the number. It increments the guess until it
 * finds the correct square root or determines that there is no integer
 * square root.
 * Return: The integer square root of n, or -1 if n does not have an integer
 * square root.
 */
int helper(int n, int guess)
{
	if (guess * guess > n)
		return (-1);
	if (guess * guess == n)
		return (guess);
	if (guess * guess < n)
		return (helper(n, guess + 1));
	return (0);
}
/**
 * _sqrt_recursion - Returns the natural square root of a number.
 * @n: The number whose square root is to be calculated.
 * Description: This function calculates the natural square root of a given
 * number using recursion. It calls the helper function to find the square root
 * by incrementing the guess until it finds the correct square root or
 * determines that there is no integer square root.
 * Return: The natural square root of n, or -1 if n does
 * not have an integer square root.
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	return (helper(n, 0));
}
