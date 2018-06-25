/*
** EPITECH PROJECT, 2018
** student
** File description:
** 22/05/18
*/

#include "server.h"

void init_file(t_file *file)
{
	file->state = NONE;
	file->target = NULL;
	file->owner = NULL;
	file->name = NULL;
}

void clear_file(t_file *file)
{
	file->name = free_secur(file->name);
	file->owner = free_secur(file->owner);
	file->target = free_secur(file->target);
	file->state = NONE;
}

int remove_file(t_irc *irc, t_file *file)
{
	clear_file(file);
	delete(file, irc->clients);
	return (0);
}

int remove_all_files(t_irc *irc)
{
	t_node *current = irc->files->head;
	t_node *next;

	while (current != NULL) {
		next = current->next;
		clear_file(current->data);
		free(current->data);
		free(current);
		current = next;
	}
	free(irc->files);
	return (0);
}
