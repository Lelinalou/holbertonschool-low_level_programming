#include "main.h"

/**
 * whatsmyname - prints the name of the program
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: void
 */
void whatsmyname(int argc, char *argv[])
{
	int i = 0;
	(void)argc;

	while (argv[0][i] != '\0')
	{
		_putchar(argv[0][i]);
		i++;
	}
	_putchar('\n');
}
