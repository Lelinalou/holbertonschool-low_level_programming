#include <stdio.h>

/**
 * whatsmyname - prints the name of the program
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: void
 */
void whatsmyname(int argc, char *argv[])
{
	(void)argc;
	printf("%s\n", argv[0]);
}
