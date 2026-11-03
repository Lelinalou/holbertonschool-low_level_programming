#include "main.h"
/*
*_string_toupper - converts all lowercase letters of a string to uppercase
*@s: the string to be converted
*Return: a pointer to the resulting string s
*/
char *string_toupper(char *s)
{
	char *start = s;

	while (*s != '\0')
	{
		if (*s >= 'a' && *s <= 'z')
		*s = *s - 32;
		s++;
	}
	return (start);
}
