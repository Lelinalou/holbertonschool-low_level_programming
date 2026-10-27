#include<stdio.h>
/**
* main - prints the alphabet in lowercase
*
* Return: Always 0 (Success)
*/
int main(void)
{
char c;
c = 'z';
while (c >= 'a')
{
putchar(c--);
}
putchar('\n');
return (0);
}