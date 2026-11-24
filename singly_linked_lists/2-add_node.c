#include "lists.h"
/**
 * add_node - adds a new node at the beginning of a list
 * @head: double pointer to the head of the list
 * @str: string to be added to the new node
 * Return: address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;

	if (head == NULL)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);

	new->str = strdup(str);
	if (new->str == NULL)
	{
		free(new);
		return (NULL);
	}
	new->len = _strlen(str);
	new->next = *head;
	*head = new;
	return (new);
}

/**
* _strlen - returns the length of a string
* @s: string to be measured
* Return: length of the string
*/
int _strlen(const char *s)
{
	int longueur = 0;

	while (s[longueur] != '\0')
	{
		longueur++;
	}
	return (longueur);
}

