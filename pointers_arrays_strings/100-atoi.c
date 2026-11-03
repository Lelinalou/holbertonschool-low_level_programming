#include "main.h"
/**
*atoi - converts a string to an integer
*@s: the string to be converted
*Return: the integer value of the string
*/
int _atoi(char *s)
{
	int i = 0;
	int digit = 0;
	int moins = 0;
	int number = 0;

	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
		moins++;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		digit = digit + 1;
		number = number * 10 + (s[i] - '0');
		i++;
	}
	if (digit == 0)
		return (0);
	if (moins % 2 != 0)
		number = -number;

	return (number);
}
