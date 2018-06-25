/*
** EPITECH PROJECT, 2018
** tools
** File description:
** tools
*/

#include "server.h"

size_t count_row(char **array)
{
	size_t i = 0;

	while (array[i] != NULL)
		++i;
	return (i);
}

void send_to_all(t_irc *irc, t_session *session, char *msg, bool filter)
{
	t_session *client = NULL;

	for (t_node *c = irc->clients->head; c != NULL ; c = c->next) {
		client = (t_session *) c->data;
		if (filter == false || (filter == true && client->nickname
			&& session->nickname && (strcmp(session->nickname,
			client->nickname) != 0))) {
			write_fd(client->control.socket, msg);
		}
	}
}

void edit_channel(t_irc *irc, t_session *session, char *newnick)
{
	t_node *c = irc->channels->head;
	t_channel *channel = NULL;
	t_member *m = NULL;

	while (c != NULL) {
		channel = (t_channel *) c->data;
		if (strcmp(channel->name, session->nickname) == 0) {
			channel->name = free_secur(channel->name);
			channel->name = strdup(newnick);
		}
		m = get_by_member_name(session->nickname, channel->members);
		if (m) {
			m->nickname = free_secur(m->nickname);
			m->nickname = strdup(newnick);
		}
		c = c->next;
	}
}
