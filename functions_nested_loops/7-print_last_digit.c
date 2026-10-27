#include "main.h"
/**
    * print_last_digit - check the code
    * @n: character to check
    * Return: the value of the last digit
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
