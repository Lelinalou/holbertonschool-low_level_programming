#include "function_pointers.h"
/**
 * int_index - searches for an integer in an array
 * @array: the array to search in
 * @size: the number of elements in the array
 * @cmp: pointer to the function used to compare values
 *
 * Return: the index of the first element for which cmp does not return 0,
 * or -1 if no element matches, if size <= 0, or if array or cmp is NULL
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int index = 0;

	if (size <= 0 || array == NULL || cmp == NULL)
		return (-1);
	while (index < size)
	{
		if (cmp(array[index]))
			return (index);
		index++;
	}
	return (-1);
}
