/*
** EPITECH PROJECT, 2018
** add_remove
** File description:
** add_remove
*/

#include "server.h"

int remove_server(t_irc *irc)
{
	FD_CLR(irc->control.socket, &irc->readfds);
	close_fd(irc->control.socket);
	if (irc->control.ip)
		free(irc->control.ip);
	return (0);
}
