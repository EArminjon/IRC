/*
** EPITECH PROJECT, 2018
** reader
** File description:
** reader
*/

#include "server.h"

int read_clients(t_irc *irc)
{
	t_node *current = irc->clients->head;
	t_session *session;

	while (current != NULL && !my_break(false)) {
		session = (t_session *) current->data;
		if (FD_ISSET(session->control.socket, &irc->readfds)) {
			if (manage_client(irc, session) == 1)
			current = irc->clients->head;
			else
			current = current->next;
		} else {
			current = current->next;
		}
	}
	return (0);
}

int get_fd_max(t_irc *irc)
{
	int fd = irc->control.socket;
	t_node *current = irc->clients->head;
	t_session *session;

	while (current != NULL) {
		session = (t_session *) current->data;
		if (session->control.socket > fd)
			fd = session->control.socket;
		current = current->next;
	}
	return (fd);
}

int read_server(t_irc *irc)
{
	struct timeval tv = {1, 0};
	int fd_max = 0;

	fd_max = get_fd_max(irc);
	if (select(fd_max + 1, &irc->readfds, NULL, NULL, &tv) == -1)
		return (fprintf(stderr, "Select failed.\n"), -1);
	if (FD_ISSET(irc->control.socket, &irc->readfds))
		return (add_client(irc));
	return (0);
}

int init_read(t_irc *irc)
{
	t_node *current = irc->clients->head;
	t_session *session;

	FD_ZERO(&irc->readfds);
	FD_SET(irc->control.socket, &irc->readfds);
	while (current != NULL) {
		session = (t_session *) current->data;
		FD_SET(session->control.socket, &irc->readfds);
		current = current->next;
	}
	return (0);
}
