/*
** EPITECH PROJECT, 2018
** getter
** File description:
** getter
*/

#include "server.h"

char *get_by_channel_name(char *name, t_list *list)
{
	t_node *current = list->head;
	char *channelname = NULL;

	while (current != NULL) {
		channelname = (char *) current->data;
		if (channelname != NULL && strcmp(channelname, name) == 0)
			return (channelname);
		current = current->next;
	}
	return (NULL);
}

t_member *get_by_member_name(char *name, t_list *list)
{
	t_node *current = list->head;
	t_member *m = NULL;

	while (current != NULL) {
		m = (t_member *) current->data;
		if (m->nickname != NULL && strcmp(m->nickname, name) == 0)
			return (m);
		current = current->next;
	}
	return (NULL);
}

t_session *get_by_session_nickname(char *name, t_list *list)
{
	t_node *current = list->head;
	t_session *s = NULL;

	while (current != NULL) {
		s = (t_session *) current->data;
		if (s->nickname != NULL && strcmp(s->nickname, name) == 0)
			return (s);
		current = current->next;
	}
	return (NULL);
}

t_channel *get_by_channel_by_name(char *name, t_list *list)
{
	t_node *current = list->head;
	t_channel *channel = NULL;

	while (current != NULL) {
		channel = (t_channel *) current->data;
		if (strcmp(channel->name, name) == 0)
			return (channel);
		current = current->next;
	}
	return (NULL);
}
