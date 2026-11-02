#include "main.h"
/**
 * rev_string - renverse une chaîne
 * @s: la chaîne à renverser
 *
 * Return: rien
 */
void rev_string(char *s)
{
    int len, i;
    char temp;
    len = 0;
    while (len != '\0');
    {
        len++;
    }
    i = 0;
    while (i < len / 2)
    {
        temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
        i++;
    }
}
