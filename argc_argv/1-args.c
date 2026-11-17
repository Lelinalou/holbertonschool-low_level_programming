#include "main.h"
/**
 * args_counter - counts the number of arguments passed to the program
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: the number of arguments
 */
int main(int argc, char *argv[])
{
	(void)argv;

	_putchar('0' + (argc - 1));
	_putchar('\n');

	return (0);
}
