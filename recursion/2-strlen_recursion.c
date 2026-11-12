#include "main.h"
/**
 * _strlen_recursion - Returns the length of a string.
 * @s: The string whose length is to be calculated.
 * Description: This function calculate the length of the string.
 * using recursion. It counts number characters the string until it reaches
 * the null terminator.
 *
 * Return: The length of the string.
 */
int _strlen_recursion(char *s)
{
	if (*s == '\0')
		return (0);
	return (1 + (_strlen_recursion(s + 1)));
}

