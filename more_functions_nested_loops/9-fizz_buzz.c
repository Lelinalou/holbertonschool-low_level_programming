#include "main.h"
/**
* fizz_buzz - prints the numbers from 1 to 100, followed by a new line
* but for multiples of three print Fizz instead of the number and for the multiples of five
* print Buzz instead of the number
* Return: void
*/
void fizz_buzz(void)
{
int i;
for(i = 0; i <= 100; i++)
{
        _putchar(i +'0');
if (i % 3 == 0 && i % 5 == 0)
{
        printf("FizzBuzz");
}
if (i % 3 == 0)
{
        printf("Fizz");
}
if (i % 5 == 0)
{
        printf("Buzz");
}
}
}
