#include "main.h"
/**
*_strncpy - copies a string
*@dest: the destination string
*@src: the source string
*@n: the number of bytes to copy from src
*Return: a pointer to the resulting string dest
*/
char *_strncpy(char *dest, char *src, int n)
{
	char *start = dest;

	while (*src != 0 && n > 0)
	{
	*dest = *src;
	src++;
	dest++;
	n--;
	}

	while (n > 0)
	{
	*dest = '\0';
	dest++;
	n--;
	}
	return (start);
}




int main(void)
{
    char s1[98];
    char *ptr;
    int i;

    for (i = 0; i < 98 - 1; i++)
    {
        s1[i] = '*';
    }
    s1[i] = '\0';
    printf("%s\n", s1);
    ptr = _strncpy(s1, "First, solve the problem. Then, write the code\n", 5);
    printf("%s\n", s1);
    printf("%s\n", ptr);
    ptr = _strncpy(s1, "First, solve the problem. Then, write the code\n", 90);
    printf("%s", s1);
    printf("%s", ptr);
    for (i = 0; i < 98; i++)
    {
        if (i % 10)
        {
            printf(" ");
        }
        if (!(i % 10) && i)
        {
            printf("\n");
        }
        printf("0x%02x", s1[i]);
    }
    printf("\n");
    return (0);
}