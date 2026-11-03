#include "main.h"
/**
*puts_half - prints half of a string, followed by a new line
*@str: the string to be printed
*Return: void
*/
void puts_half(char *str)
{
	int len = 0;
	int i = 0;

	while (str[len] != '\0')
		len++;
	if (len % 2 != 0)
		len++;
	for (i = len / 2; str[i] != '\0'; i++)
		_putchar(str[i]);
	
_putchar('\n');
}
