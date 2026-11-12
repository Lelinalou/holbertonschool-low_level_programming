#include "main.h"
/**
 * _pow_recursion - Returns the value of x raised to the power of y.
 * @x: The base number.
 * @y: The exponent.
 * Description: This function calculates the value of x raised to the pow of y
 * using recursion. It multiplies x by the result of x raised to the power of y
 * decremented by 1 until it reaches the base case of y being 0.
 * Return: The value of x raised to the power of y, or -1 if y
 * is negative.
 */
int _pow_recursion(int x, int y)
{
	if (y < 0)
		return (-1);
	if (y == 0)
		return (1);
	return (x * _pow_recursion(x, y - 1));
}
