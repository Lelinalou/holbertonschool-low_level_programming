#include "main.h"
/**
 * main - check the code
 *
 * Return: Always 0.
 */
void print_alphabet(void)
{
char a = 'a';
char z = 'z';
for (a = 'a'; a != z+1; a++)
{
_putchar(a);
}  
_putchar('\n');
}
