#include "main.h"
/**
 * print_alphabet - check the code
 *
 * Return: Always 0.
 */
void print_alphabet_x10(void)
{
char a = 'a';
int compteur = 0;
for (compteur = 0; compteur <= 9; compteur++)
{
for (a = 'a'; a != 'z' + 1; a++)
{
_putchar(a);
}
_putchar('\n');
}
}
