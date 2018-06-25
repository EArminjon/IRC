/*
** EPITECH PROJECT, 2018
** linked
** File description:
** linked
*/

#include "server.h"

t_node *createt_node(void *data)
{
	t_node *newt_node = malloc(sizeof(t_node));

	if (newt_node == NULL)
		return (fprintf(stderr, "Out of memory.\n"), NULL);
	newt_node->data = data;
	newt_node->next = NULL;
	return (newt_node);
}

t_list *emptyt_list(void)
{
	t_list *list = malloc(sizeof(t_list));

	if (list == NULL)
		return (fprintf(stderr, "Out of memory.\n"), NULL);
	list->head = NULL;
	return (list);
}

void add(void *data, t_list *list)
{
	t_node *current = NULL;

	if (list->head == NULL) {
		list->head = createt_node(data);
	} else {
		current = list->head;
		while (current->next != NULL)
			current = current->next;
		current->next = createt_node(data);
	}
}

size_t count(t_list *list)
{
	size_t size = 0;
	t_node *current = list->head;

	while (current != NULL) {
		size += 1;
		current = current->next;
	}
	return (size);
}
