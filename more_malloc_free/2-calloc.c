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
	unsigned int i = 0;

	if (size == 0)
		return (NULL);
	if (nmemb == 0)
		return (NULL);
	p = malloc(nmemb * size);
	if (p == 0)
		return (NULL);
	while (i < nmemb * size)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
