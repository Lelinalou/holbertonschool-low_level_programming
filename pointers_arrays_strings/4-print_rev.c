#include "main.h"
/**
* print_rev - prints a string in reverse, followed by a new line
* @s: string to be printed in reverse
* Return: void
*/
void print_rev(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		_putchar(s[i]);      

	int len = 0;
	
	while (len >= 0)
	{
		_putchar(s[len]);
		len++;
	}
	while (len > 0)
	{
		_putchar(s[i]);
		len--;
	}
}
