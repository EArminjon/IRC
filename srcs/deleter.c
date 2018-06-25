/*
** EPITECH PROJECT, 2018
** delete
** File description:
** delete
*/

#include "server.h"

void delete(void *data, t_list *list)
{
	t_node *current = list->head;
	t_node *previous = current;

	while (current != NULL) {
		if (current->data == data) {
			previous->next = current->next;
			if (current == list->head)
			list->head = current->next;
			if (current->data != NULL)
			free(current->data);
			current->data = NULL;
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

bool delete_if_member(void *data, t_list *list)
{
	t_node *current = list->head, *previous = current;
	t_member *member = NULL;
	char *name = (char *)data;

	while (current != NULL) {
		member = (t_member *)current->data;
		if ((strcmp(member->nickname, name)) == 0) {
			previous->next = current->next;
			if (current == list->head)
			list->head = current->next;
			if (current->data != NULL)
			free(current->data);
			current->data = NULL;
			free(current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
}
