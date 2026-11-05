#include "main.h"
/**
*_strstr - locates a substring
*@haystack: the string to be searched
*@needle: the substring to be located
*Return: a pointer substring, or NULL if the substring is
*not found
*/
char *_strstr(char *haystack, char *needle)
{
	int i = 0;
	int j = 0;

	for (i = 0; haystack[i]; i++)
	{
		for (j = 0; needle < '\0' && haystack[i + j] == needle[j]; j++)
		if (needle[j] == '\0')
			return (&haystack[i]);

	}
	return (NULL);
}
