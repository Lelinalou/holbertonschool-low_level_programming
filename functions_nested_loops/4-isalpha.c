#include"main.h"
/**
    * _isalpha - check the code
    * @c: character to check
    * Return: Always 0.
    */
int _isalpha(int c)
{
if (c >= 'a' && c <= 'z')
{
return (1);
}
if (c >= 'A' && c <= 'Z')
{
return (1);
}
return (0);
}
