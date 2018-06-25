/*
** EPITECH PROJECT, 2018
** server
** File description:
** server
*/

#include "server.h"

void init_server(t_irc *irc, int port)
{
	my_signal();
	irc->clients = emptyt_list();
	irc->channels = emptyt_list();
	irc->nb_client = 0;
	irc->control.port = (in_port_t) port;
	irc->control.ip = strdup("127.0.0.1");
	irc->files = emptyt_list();
}

int server(int port)
{
	t_irc irc;
	int error = 0;

	init_server(&irc, port);
	if (create_socket(&irc.control, "TCP") == false)
		return (84);
	while (error == 0 && !my_break(false)) {
		init_read(&irc);
		error = read_server(&irc);
		read_clients(&irc);
	}
	remove_all_clients(&irc);
	remove_all_channels(&irc);
	remove_server(&irc);
	remove_all_files(&irc);
	return (0);
}
