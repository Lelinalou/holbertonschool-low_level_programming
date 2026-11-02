#include "main.h"
/**
* _strlen - returns the length of a string
* @s: string to be measured
* Return: length of the string
*/
int _strlen(char *s)
{
	int longueur = 0;

	while (s[longueur] != '\0')
	{
		longueur++;
	}
	return (longueur);
}
