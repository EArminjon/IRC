/*
** EPITECH PROJECT, 2018
** socket
** File description:
** socket
*/

#include "server.h"

bool create_socket(t_com *c, char *proto_name)
{
	struct protoent *pe = getprotobyname(proto_name);

	if (!pe)
		return (fprintf(stderr, "Getprotobyname failed.\n"), false);
	c->socket = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (c->socket == -1)
		return (fprintf(stderr, "Socket creation failed.\n"), false);
	if (setsockopt(c->socket, SOL_SOCKET, SO_REUSEADDR,
		&(int){1}, sizeof(int)) < 0)
		return (fprintf(stderr,  "setsockopt failed)"), false);
	c->s_in.sin_family = AF_INET;
	c->s_in.sin_port = htons(c->port);
	c->s_in.sin_addr.s_addr = INADDR_ANY;
	if ((bind(c->socket, (const struct sockaddr *)&c->s_in,
		sizeof(c->s_in))) == -1)
		return (close(c->socket), false);
	if (listen(c->socket, 42) != -1)
		return (true);
	return (fprintf(stderr, "Listen failed.\n") , false);
}

bool connect_socket(t_com *com, char *proto_name)
{
	struct protoent *pe;

	pe = getprotobyname(proto_name);
	if (!pe)
		return (fprintf(stderr, "Getprotobyname fail\n"), false);
	com->socket = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (com->socket == -1)
		return (fprintf(stderr, "Socket fail\n"), false);
	com->s_in.sin_family = AF_INET;
	com->s_in.sin_port = htons((uint16_t) com->port);
	com->s_in.sin_addr.s_addr = inet_addr(com->ip);
	if (connect(com->socket, (struct sockaddr *) &com->s_in,
			sizeof(com->s_in)) == -1) {
		if (close(com->socket) == -1)
			return (fprintf(stderr, "Close 2 fail\n"), false);
		return (fprintf(stderr, "Close 2\n"), false);
	}
	return (true);
}
