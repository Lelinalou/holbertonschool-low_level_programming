#include "main.h"
/**
* more_numbers - prints numbers from 0 to 14, 10 times
* Return: void
*/
void more_numbers(void)
{
int ligne, n;
for ligne (ligne == 0; ligne < 10; ligne++)
{
for  (n == 0; n <= 14; n++)
{
if (n > 9)
{
_putchar('0' + n / 10);
}
_putchar('0' + n % 10);
}
_putchar('\n);
}
