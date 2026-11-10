#include "dog.h"
/**
 * free_dog - Prints the information of a struct dog.
 * @d: Pointer to the struct dog to print.
 * Description: This function prints The name, age, and owner of a struct dog.
 * If any of the fields are NULL, it prints "(nil)" for that field.
 */
void free_dog(dog_t *d)
{
	if (d == NULL)
		return;
	if (d->name == NULL)
	{
		free(d);
		return;
	}
	if (d->owner == NULL)
	{
		free(d);
		free(d->name);
		return;
	}
}
