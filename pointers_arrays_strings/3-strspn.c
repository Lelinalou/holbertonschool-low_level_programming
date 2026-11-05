#include "main.h"
/**
*_strspn - gets the length of a prefix substring
*@s: the string to be searched
*@accept: the string containing the characters to match
*Return: the number of bytes in the initial segment of s which consist only of bytes from
*accept
*/
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i = 0;   /*compter*/
	int j = 0;   /*parcourir accept*/
	int trouve;

	for(i = 0; s[i] != '\0'; i++)
	{
		trouve = 0;
		j = 0;
		while (accept[j] != '\0' && trouve == 0)
			{
				if (s[i] == accept[j])
					trouve = 1;
				j++;
			}
			if (trouve == 0)
				return (i);
	}
	return (i);
}
