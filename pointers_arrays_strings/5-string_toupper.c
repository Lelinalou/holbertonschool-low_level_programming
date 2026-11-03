#include "main.h"
/**
 * string_toupper - changes all lowercase letters of a string to uppercase
 * @s: pointer to the string to modify
 *
 * Return: pointer to the modified string
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
