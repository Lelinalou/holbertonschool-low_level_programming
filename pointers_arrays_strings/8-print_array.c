#include "main.h"
/**
*print_array - prints n elements of an array of integer, followed by a new line
*@a: the array to be printed
*@n: the number of elements of the array to be printed
*Return: void
*/
void print_array(int *a, int n)
{
	int i = 0;

	while (i < n)
	{
		if (i != 0)
		{
			printf(", ");
		}
		printf("%d", a[i]);
		i++;
	}
	printf("\n");
}
