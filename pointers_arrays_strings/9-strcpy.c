#include "main.h"
/**
*_strcpy - copies the string pointed to by src
*@dest: the destination buffer
*@src: the source string to be copied
*Return: a pointer to the destination string dest
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
return (dest);
}
