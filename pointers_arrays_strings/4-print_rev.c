#include "main.h"

/**
 * print_rev - affiche une chaîne en sens inverse, puis un retour à la ligne
 * @s: la chaîne à afficher
 *
 * Return: rien
 */
void print_rev(char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
		len++;

	while (len > 0)
	{
		len--;
		_putchar(s[len]);
	}
	_putchar('\n');
}
