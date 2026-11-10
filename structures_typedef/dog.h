#ifndef DOG_H
#define DOG_H
#include <stdio.h>
/**
 * struct dog - a dog's basic info
 * @name: name of the dog
 * @age: age of the dog
 * @owner: name of the dog's owner
 *
 * Description: This struct stores information about a dog, including its
 * name, age, and the name of its owner.
 */
struct dog
{
	char *name;
	float age;
	char *owner;
};

#endif
