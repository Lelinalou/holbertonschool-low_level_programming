#include<stdio.h>
/**
* main - prints the numbers from 0 to 9
*
* Return: Always 0 (Success)
*/
int main(void)
{
int n;
n = 48;
while (n <= 57)
{
putchar(n);
if (n < 57)
{
putchar(',');
putchar(' ');
}
n = n + 1;
}
putchar('\n');
return (0);
}
