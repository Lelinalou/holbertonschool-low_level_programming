#include "function_pointers.h"
/**
 * array_iterator - executes a function given as a parameter on each element
 * of an array.
 * @array: The array to iterate over.
 * @size: The size of the array.
 * @action: A pointer to a function that takes an integer as an argument and
 * returns void.
 * Description: This function takes an array of integers, its size, and a
 * function pointer as parameters. It iterates over each element of the array
 * and applies the function pointed to by action to each element.
 * If the array or the function pointer is NULL, the function does nothing.
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t i = 0;

	if (array == NULL || action == NULL)
		return;
	while (i < size)
	{
		action(array[i]);
		i++;
	}
}
