#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/**
*malloc_checked - allocates memory using malloc and checks for success
*@b: size of memory to allocate
*Return: pointer to the allocated memory, or exit with status 98 if it fails
*/
void *malloc_checked(unsigned int b)
{
	void *p;

	p = malloc(b);
	if (p == NULL)
		exit(98);
	else
		return (p);
}
