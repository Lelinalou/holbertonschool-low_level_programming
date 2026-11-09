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
	char *p;