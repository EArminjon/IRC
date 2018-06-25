/*
** EPITECH PROJECT, 2018
** names
** File description:
** names
*/

#include "server.h"

int nick_function(t_irc *irc, t_session *s, char **tab)
{
	char *msg = NULL;
	t_session *other = NULL;

	if (tab[0] == NULL)
		return (dprintf(s->control.socket, ":%s 431 ERR_NONICK"
		"NAMEGIVEN :No nickname given%s", irc->control.ip, ENDL), 0);
	other = get_by_session_nickname(tab[0], irc->clients);
	if (other != NULL)
		return (dprintf(s->control.socket, ":%s 433 ERR_NICKNAMEINUSE "
		":%s is already in use%s", irc->control.ip, tab[0], ENDL), 0);
	if (s->nickname != NULL) {
		edit_channel(irc, s, tab[0]);
		asprintf(&msg, ":%s NICK %s%s", s->nickname, tab[0], ENDL);
		send_to_all(irc, s, msg, false);
		msg = free_secur(msg);
		s->nickname = free_secur(s->nickname);
	}
	s->nickname = strdup(tab[0]);
	s->connected = true;
	return (0);
}

int names_one_function(t_irc *irc, t_session *s, t_channel *channel)
{
	char *name = NULL;
	t_node *c = NULL;
	t_member *m = NULL;

	if (channel && channel->members != NULL) {
		dprintf(s->control.socket, ":%s 353 RPL_NAMREPLY %s%s",
			irc->control.ip, channel->name, ENDL);
		for (c = channel->members->head; c != NULL ; c = c->next) {
			m = (t_member *) c->data;
			if (m->nickname != NULL)
			dprintf(s->control.socket, ":%s%s", m->nickname, ENDL);
		}
	}
	name = (channel != NULL) ? channel->name : "";
	dprintf(s->control.socket, ":%s 366 RPL_ENDOFNAMES %s :End of /N"
		"AMES list%s", irc->control.ip, name, ENDL);
	return (0);
}

int names_function(t_irc *irc, t_session *session, char **tab)
{
	t_node *c = NULL;

	if (*tab != NULL)
		return names_one_function(irc, session,
			get_by_channel_by_name(*tab, irc->channels));
	for (c = irc->channels->head; c != NULL ; c = c->next)
		names_one_function(irc, session, (t_channel *)c->data);
	return (0);
}
