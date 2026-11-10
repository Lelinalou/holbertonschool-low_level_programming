#include "dog.h"
/**
 * print_dog - Prints the information of a struct dog.
 * @d: Pointer to the struct dog to print.
 *
 Description: This function prints the name, age, and owner of a struct dog.
 * If the pointer is NULL, it does nothing.
 */
void print_dog(struct dog *d)
{
	if (d == NULL)
		return;
	if(d->name == NULL)
		printf("(nil)");
	if(d->owner == NULL)
		printf("(nil)");
	printf("Name: %s\n", d->name);
	printf("Age: %.6f\n", d->age);
	printf("Owner: %s\n", d->owner);
}
