#include "dog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * File: dog.c
 * Auth: Your Name
 */
/**
 * init_dog - Initializes a struct dog with the given parameters.
 * @d: Pointer to the struct dog to initialize.
 * @name: Name of the dog.
 * @age: Age of the dog.
 * @owner: Name of the dog's owner.
 *
 * Description: This function initializes a struct dog with the provided
 * name, age, and owner. It sets the corresponding fields of the struct to
 * the provided values.
 */
void init_dog(struct dog *d, char *name, float age, char *owner)
{
	d->name = name;
	d->age = age;
	d->owner = owner;
}
