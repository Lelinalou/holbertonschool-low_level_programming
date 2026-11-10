#include "main.h"
/**
*string_nconcat - concatenates two strings, up to n bytes from s2
*@s1: first string
*@s2: second string
*@n: number of bytes to concatenate from s2
*Return: pointer to the concatenated string, or NULL if it fails
*/
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	unsigned int len1 = 0;
	unsigned int len2 = 0;
	unsigned int i1 = 0;
	unsigned int i2 = 0;
	char *p;

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
	if (n >= len2)
		n = len2;

	p = malloc((len1 + n + 1) * sizeof(char));
	if (p == 0)
	{
		return (NULL);
	}
	while (s1[i1] != '\0')
	{
		p[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] != '\0' && i2 < n)
	{
		p[i1 + i2] = s2[i2];
		i2++;
	}
	p[i1 + i2] = '\0';
	return (p);
}
