#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
*_calloc - allocates memory for an array of nmemb elements of size bytes each
*@nmemb: number of elements
*@size: size of each element
*Return: pointer to the allocated memory, or NULL if it fails
*/
void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned char *p;

	p = malloc(nmemb * sizeof(size));
	if (p == 0)
		return (NULL);
	if (size == 0)
		return (NULL);
	if (nmemb == 0)
		return (NULL);

	return (p);
}
