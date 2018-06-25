/*
** EPITECH PROJECT, 2018
** user_users
** File description:
** user_users
*/

#include "server.h"

int users_norm_function(t_irc *irc, t_session *session, bool empty)
{
	if (empty)
		dprintf(session->control.socket, ":%s 395 RPL_NOUSERS :Nobod"
		"y logged in%s", irc->control.ip, ENDL);
	return (dprintf(session->control.socket, ":%s 394 RPL_ENDOFUSERS :End "
		"of users%s", irc->control.ip, ENDL), 0);
}

int users_function(t_irc *irc, t_session *session, char **tab)
{
	bool empty = true;
	t_node *c;
	t_session *member;

	(void) tab;
	dprintf(session->control.socket, ":%s 392 RPL_USERSSTART :UserID Termi"
		"nal Hôte%s", irc->control.ip, ENDL);
	if (irc->clients != NULL)
		for (c = irc->clients->head; c != NULL ; c = c->next) {
			member = (t_session *) c->data;
			if (member->nickname != NULL) {
			empty = false;
			dprintf(session->control.socket, ":%s 393 RPL_USERS :"
			"%s%s", irc->control.ip, member->nickname, ENDL);
			}
		}
	return (users_norm_function(irc, session, empty));
}

int user_function(t_irc *irc, t_session *session, char **buffer)
{
	if (count_row(buffer) < 3)
		return (dprintf(session->control.socket,
		":%s 461 ERR_NEEDMOREPARAMS USER :Not enough parameters%s",
		irc->control.ip, ENDL));
	session->username = strdup(buffer[0]);
	session->host = strdup(buffer[1]);
	session->server = strdup(buffer[2]);
	session->realname = strdup(buffer[3]);
	dprintf(session->control.socket,
		":%s 001 %s :Welcome to the IRC Network %s!%s@%s%s",
		irc->control.ip,
		session->nickname,
		session->nickname,
		session->username,
		session->control.ip,
		ENDL);
	return (0);
}
