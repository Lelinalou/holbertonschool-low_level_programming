#include "main.h"
/**
* main - prints the numbers from 0 to 9
*
* Return: Always 0 (Success)
*/
int main(void)
{
char *c = "_putchar";
int compteur = 0;
while (compteur < 8)
{
_putchar(c[compteur]);
compteur = compteur + 1;
}
_putchar('\n');
return (0);
}
