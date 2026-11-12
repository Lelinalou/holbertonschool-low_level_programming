#include "main.h"
/**
*_print_rev_recursion - Prints a string in reverse followed by a new line.
*@s: The string to be printed in reverse.
*Description: This function prints the string pointed to by 's' in reverse ord
*It prints each character of the string one by one in reverse until it reaches
*the beginning of the string.
*/
void _print_rev_recursion(char *s)
{
	if (*s == '\0')
	{
		return;
	}
	_print_rev_recursion(s + 1);
	_putchar(*s);
}
