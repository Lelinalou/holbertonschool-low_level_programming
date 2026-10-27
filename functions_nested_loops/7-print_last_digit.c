#include "main.h"
/**
    * print_last_digit - check the code
    * @c: character to check
    * Return: Always 0.
    */
int print_last_digit(int n)
{
int last;
last = n % 10;
if (last < 0)
{
last = -last;
}
_putchar(last + '0');
return (last);
}
