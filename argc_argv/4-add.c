#include "main.h"
/**
*main - adds positive numbers
* @argc: number of arguments
* @argv: array of arguments
* Return: Always 0 (Success)
*/

int main(int argc, char *argv[])
{
	int i, j, result;

	for (i = 1; i < argc; i++)
	{
		for (j = 0; argv[i][j] != '\0'; j++)
		{
			if (argv[i][j] < '0' || argv > '9')
			{
			printf("Error\n");
			return (1);
			}
		}
		result = result + atoi(argv[i]);
	}
	return (0);
}
