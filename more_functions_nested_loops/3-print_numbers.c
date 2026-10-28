#include "main.h"
/**
 * print_numbers - prints numbers from 0 to 9 followed by a new line
 * Return: void
 */
void print_numbers(void)
{
int compteur;
for (compteur = 0; compteur <= 9; compteur++)
{
_putchar('0' + compteur);
}
_putchar('\n');
}
