#include "main.h"
/**
* print_rev - prints a string in reverse, followed by a new line
* @s: string to be printed in reverse
* Return: void
*/
void print_rev(char *s)
{
	int longueur = 0;

	while (s[longueur] != '\0')
	{
		longueur++;

	while (longueur > 0)
	{
		longueur--;
		_putchar(s[longueur]);
	}
	}
	_putchar('\n');
}
