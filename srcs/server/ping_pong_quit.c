/*
** EPITECH PROJECT, 2018
** ping_pong_quit
** File description:
** ping_pong_quit
*/

#include "server.h"

int quit_function(t_irc *irc, t_session *session, char **tab)
{
	(void) tab;
	remove_client(irc, session);
	return (1);
}

int pong_function(t_irc *irc, t_session *session, char **tab)
{
	(void) tab;
	(void) irc;
	session->ping.enable = false;
	return (0);
}

int ping_function(t_irc *irc, t_session *session, char **tab)
{
	(void) tab;
	(void) irc;
	dprintf(session->control.socket, ":%s 000 PONG %s%s",
		irc->control.ip, tab[0], ENDL);
	return (0);
}
