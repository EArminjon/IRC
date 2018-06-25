/*
** EPITECH PROJECT, 2018
** add_remove
** File description:
** add_remove
*/

#include "server.h"

void init_channel(t_channel *channel, char *name, char *owner)
{
	channel->name = strdup(name);
	channel->owner = strdup(owner);
	channel->members = emptyt_list();
}

int add_channel(t_irc *irc, char *name, char *owner)
{
	t_channel *channel = malloc(sizeof(*channel));

	if (channel == NULL)
		return (fprintf(stderr, "Out of memory.\n"), 84);
	init_channel(channel, name, owner);
	add(channel, irc->channels);
	return (0);
}

void init_member(t_member *member, t_session *session)
{
	member->nickname = strdup(session->nickname);
	member->fd = session->control.socket;
}