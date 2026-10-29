#include "main.h"

/**
 * print_triangle - prints a right-aligned triangle using '#'
 * @size: size of the triangle
 *
 * Description: Row i (1-based) has (size - i) leading spaces
 * followed by i '#' characters. If size <= 0, only a newline
 * is printed.
 */
void print_triangle(int size)
{
	int row, col;

	if (size <= 0)
	{
		_putchar('\n');
		return;
	}

	for (row = 1; row <= size; row++)
	{
		for (col = 0; col < size - row; col++)
			_putchar(' ');

		for (col = 0; col < row; col++)
			_putchar('#');

		_putchar('\n');
	}
}
