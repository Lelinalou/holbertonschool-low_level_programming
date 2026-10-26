#include<stdio.h>
/**
    * main - prints the alphabet in lowercase
    *
    * Return: Always 0 (Success)
    */
int main(void)
{
char c;
c = 'a';
while (c <= 'z')
{
putchar(c++);
}
putchar('\n');
return (0);
}