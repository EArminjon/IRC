/*
** EPITECH PROJECT, 2018
** add_remove
** File description:
** add_remove
*/

#include "server.h"

void init_client(t_session *session)
{
	session->nickname = NULL;
	session->username = NULL;
	session->channels = emptyt_list();
	session->host = NULL;
	session->server = NULL;
	session->realname = NULL;
	session->ping.enable = false;
	session->ping.time = time(NULL);
	session->connected = false;
}

void init_network(t_session *session, int fd, struct sockaddr_in *client,
			t_irc *irc)
{
	struct sockaddr_in *pV4Addr = client;
	struct in_addr ipAddr = pV4Addr->sin_addr;
	char str[INET_ADDRSTRLEN];

	session->control.socket = fd;
	session->control.s_in = *client;
	session->control.port = (in_port_t) irc->control.socket;
	session->control.ip = strdup(inet_ntop(AF_INET,
			&ipAddr, str, INET_ADDRSTRLEN));
}