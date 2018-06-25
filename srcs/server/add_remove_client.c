/*
** EPITECH PROJECT, 2018
** add_remove
** File description:
** add_remove
*/

#include "server.h"

int add_client(t_irc *irc)
{
	struct sockaddr_in client;
	socklen_t size = sizeof(client);
	int cs;
	t_session *session = malloc(sizeof(*session));

	if (session == NULL)
		return (fprintf(stderr, "Out of memory.\n"));
	printf("New client\n");
	cs = accept(irc->control.socket, (struct sockaddr *) &client, &size);
	if (cs == -1)
		return (fprintf(stderr, "Accept failed.\n"), -1);
	init_client(session);
	init_network(session, cs, &client, irc);
	add(session, irc->clients);
	irc->nb_client += 1;
	return (0);
}

void clear_client(t_irc *irc, t_session *session)
{
	FD_CLR(session->control.socket, &irc->readfds);
	close_fd(session->control.socket);
	free_secur(session->control.ip);
	free_secur(session->nickname);
	free_secur(session->username);
	free_secur(session->host);
	free_secur(session->server);
	free_secur(session->realname);
	irc->nb_client -= 1;
}

int remove_client_from_channels(t_irc *irc, t_session *session)
{
	t_node *current = irc->channels->head;
	t_channel *channel = NULL;

	while (current != NULL) {
		channel = (t_channel *) current->data;
		delete_if_member(session->nickname, channel->members);
		if (count(channel->members) == 0) {
			channel->owner = free_secur(channel->owner);
			channel->name = free_secur(channel->name);
			delete(channel, irc->channels);
			current = irc->channels->head;
		} else
			current = current->next;
	}
	return (0);
}

int remove_client(t_irc *irc, t_session *session)
{
	char *msg = NULL;

	fprintf(stderr, "Un client quitte.\n");
	asprintf(&msg, ":%s QUIT :Connection closed%s",
		session->nickname, ENDL);
	send_to_all(irc, session, msg, true);
	free_secur(msg);
	remove_client_from_channels(irc, session);
	clear_client(irc, session);
	delete(session, irc->clients);
	return (0);
}

int remove_all_clients(t_irc *irc)
{
	t_node *current = irc->clients->head;
	t_node *next;

	while (current != NULL) {
		next = current->next;
		clear_client(irc, current->data);
		free(current->data);
		free(current);
		current = next;
	}
	free(irc->clients);
	return (0);
}
