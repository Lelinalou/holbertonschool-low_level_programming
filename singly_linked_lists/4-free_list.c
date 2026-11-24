#include "lists.h"
/**
 * free_list - frees a list
 * @head: pointer to the head of the list
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head != NULL)
	{
		next = head->next;
		free(head->str);
		free(head);
		head = next;
	}
}
