#include "main.h"
/**
*str_concat - concatenates two strings
*@s1: first string
*@s2: second string
*Return: pointer to the concatenated string, or NULL if it fails
*/
char *str_concat(char *s1, char *s2)
{
	char *p;
	int len1 = 0;
	int len2 = 0;
	int i1 = 0;
	int i2 = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	while (s1[len1] != '\0')
	{
		len1++;
	}
	while (s2[len2] != '\0')
	{
		len2++;
	}
	p = malloc((len1 + len2 + 1) * sizeof(char));
	if (p == 0)
	{
		return (NULL);
	}
	while (s1[i1] != '\0')
	{
		p[i1] = s1[i1];
		i1++;
	}

	while (s2[i2] != '\0')
	{
		p[i1 + i2] = s2[i2];
		i2++;
	}
	p[i1 + i2] = '\0';
	return (p);
}
