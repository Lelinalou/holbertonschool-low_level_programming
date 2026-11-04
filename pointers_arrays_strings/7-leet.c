#include "main.h"
/**
*leet - encodes a string into 1337
*@s: the string to be encoded
*Return: a pointer to the resulting string s
*/
char *leet(char *s)
{
	char *lettre = "aAeEoOtTlL";
	char *nombre = "4433007711";
	int i = 0;
	int j = 0;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; j < 10; j++)
		{
		if (s[i] == lettre[j])
		{
		s[i] = nombre[j];
		}
		}
	}
	return (s);
}
