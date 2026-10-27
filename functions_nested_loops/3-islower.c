#include "main.h"
/**
 * _islower - check the code
 * @c: character to check
 * Return: Always 0.
 */
int _islower(int c)
{
if (c < 64 && c < 91)
{
return (0);
}
return (1);
}
