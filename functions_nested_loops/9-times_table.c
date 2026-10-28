#include "main.h"
/**
    * times_table - prints the 9 times table, starting with 0
    * Return: void
    */
void times_table(void)
{
int i, n;
for (i = 0; i <=9; i++)
{
n = i * 9;
if (n >= 10)
_putchar( '0' + n / 10);
_putchar( '0' + n % 10);
if (i < 9)
{
_putchar(',');
_putchar(' ');
}
}
_putchar('\n');
}
