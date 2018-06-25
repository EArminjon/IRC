/*
** EPITECH PROJECT, 2018
** add_remove
** File description:
** add_remove
*/

#include "server.h"

int join_channel(t_irc *irc, t_session *session, char *name)
{
	t_channel *channel = get_by_channel_by_name(name, irc->channels);
	t_member *member = malloc(sizeof(*member));

	if (channel == NULL) {
		if (add_channel(irc, name, session->nickname) == 84)
			return (fprintf(stderr, "JOIN FAILED.\n"), 84);
		channel = get_by_channel_by_name(name, irc->channels);
	}
	init_member(member, session);
	add(member, channel->members);
	add(strdup(channel->name), session->channels);
	return (0);
}

int leave_channel(t_irc *irc, t_session *session, char *name)
{
	t_channel *channel = get_by_channel_by_name(name, irc->channels);
	char *mychannel = get_by_channel_name(name, session->channels);

	if (channel == NULL || mychannel == NULL)
		return (fprintf(stderr, "PART Channel not found.\n"), 0);
	delete_if_member(session->nickname, channel->members);
	if (count(channel->members) == 0) {
		channel->owner = free_secur(channel->owner);
		channel->name = free_secur(channel->name);
		delete(channel, irc->channels);
	}
	delete(mychannel, session->channels);
	return (0);
}

int remove_all_members(t_channel *channel)
{
	t_node *current = channel->members->head;
	t_node *next;

	while (current != NULL) {
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	free(channel->members);
	return (0);
}

void clear_channel(t_channel *channel)
{
	if (channel->owner != NULL)
		free(channel->owner);
	if (channel->name != NULL)
		free(channel->name);
	remove_all_members(channel);
}

int remove_all_channels(t_irc *irc)
{
	t_node *current = irc->channels->head;
	t_node *next;

	while (current != NULL) {
		next = current->next;
		clear_channel(current->data);
		free(current->data);
		free(current);
		current = next;
	}
	free(irc->channels);
	return (0);
}
