#include "main.h"
/**
*_strspn - gets the length of a prefix substring
*@s: the string to be searched
*@accept: the string containing the characters to match
*Return: the number of bytes in the initial segment of s which consist only of bytes from accept
*/
char *_strpbrk(char *s, char *accept)
{
	int i = 0;
	int j = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
				return (&s[i]);
		}
	}
	return (NULL);
}
