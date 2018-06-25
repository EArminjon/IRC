/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/05/18
*/

#include "server.h"

bool is_ping_fail(t_session *s)
{
	return (s->ping.enable && ((time(NULL) - s->ping.time) >= 5));
}

int send_ping_request(t_session *s, t_irc *irc)
{
	if (is_ping_fail(s) && is_valid_fd(s->control.socket)) {
		remove_client(irc, s);
		return (1);
	} else if (!s->ping.enable && (time(NULL) - s->ping.time) >= 2) {
		dprintf(s->control.socket, ":%s PING %s%s",
			s->control.ip, s->nickname, ENDL);
		s->ping.enable = true;
		s->ping.time = time(NULL);
	}
	return (0);
}

void stop_ping(t_session *session)
{
	if (session->ping.enable)
		session->ping.enable = false;
}
