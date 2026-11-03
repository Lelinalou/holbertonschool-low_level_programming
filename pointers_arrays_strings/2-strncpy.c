#include "main.h"
/**
*_strncpy - copies a string
*@dest: the destination string
*@src: the source string
*@n: the number of bytes to copy from src
*Return: a pointer to the resulting string dest
*/
char *_strncpy(char *dest, char *src, int n)
{
	char *start = dest;

	while (*src != 0 && n > 0)
	{
	*dest = *src;
	src++;
	dest++;
	n--;
	}

	while (n > 0)
	{
	*dest = '\0';
	dest++;
	n--;
	}
}
