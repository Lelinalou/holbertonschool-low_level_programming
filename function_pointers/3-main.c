#include "3-calc.h"
#include<stdarg.h>
/**
 * main - Entry point
 * @argc: The number of arguments passed to the program
 * @argv: An array of strings representing the arguments
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
int num1;
int num2;
int (*p)(int, int);

if (argc != 4)
{
	printf("Error\n");
	exit(98);
}

p = get_op_func(argv[2]);
if (p == NULL)
{
	printf("Error\n");
	exit(99);
}

num1 = atoi(argv[1]);
num2 = atoi(argv[3]);

if ((argv[2][0] == '/' || argv[2][0] == '%') && (num2 == 0 || num1 == 0))
{
	printf("Error\n");
	exit(100);
}
printf("%d\n", p(num1, num2));
return (0);
}
