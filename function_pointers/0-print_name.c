#include <stdio.h>
#include "function_pointers.h"
/**
 * print_name - prints a name using a function pointer
 * @name: The name to print
 * @f: A pointer to a function that takes a string as an argument and
 * Description: This function takes a string (name) and a function )
 * It checks if either the name or the function pointer is NULL. If either
 * the function returns without doing anything. Otherwise, it calls
 * the function pointed to by f,
 * passing the name as an argument, effectively printing the name using the
 */

void print_name(char *name, void (*f)(char *))
{
	if (name == NULL || f == NULL)
		return;
	f(name);
}
