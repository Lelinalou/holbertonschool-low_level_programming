#include <stdio.h>

/**
 * main - prints the hexadecimal numbers from 0 to 15
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
int c;
int n;
c = 97;
n = 48;
while (n <= 57)
{
putchar(n);
n++;
}
while (c <= 102)
{
putchar(c);
c++;
}
putchar('\n');
return (0);
}
