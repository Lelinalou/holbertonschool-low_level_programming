#include "main.h"
/**
*strcpy - copies the string pointed to by src, including the terminating null byte (\0), to the buffer pointed to by dest
*@dest: the destination buffer
*@src: the source string to be copied
*Return: a pointer to the destination string dest
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while(src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
return (0);
}
