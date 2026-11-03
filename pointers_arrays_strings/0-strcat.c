#include "main.h"
/**
*_strcat - concatenates two strings
*@dest: the destination string
*@src: the source string
*Return: a pointer to the resulting string dest
*/
char *_strcat(char *dest, char *src)
{
	int lendeux = 0;
	int len = 0;
	for (len =0; dest[len] != '\0'; len++);
	for (lendeux = 0; src[lendeux] != '\0'; lendeux++)
	{
	dest[len + lendeux] = src[lendeux];
	}
	

