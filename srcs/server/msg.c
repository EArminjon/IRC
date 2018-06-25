/*
** EPITECH PROJECT, 2018
** msg
** File description:
** msg
*/

#include "server.h"

void send_to_channel(t_session *s, t_channel *channel, char *msg, bool filter)
{
	t_member *member = NULL;

	if (!channel) {
		fprintf(stderr, "Channel is null\n");
		return ;
	}
	for (t_node *c = channel->members->head; c != NULL ; c = c->next) {
		member = (t_member *) c->data;
		if ((filter == false) || (filter == true &&
			(strcmp(member->nickname, s->nickname) != 0)))
			dprintf(member->fd, msg);
	}
}

int send_privmsg(t_irc *irc, t_session *s, char **tab)
{
	char *target_name = NULL, *msg = NULL;
	t_session *target = NULL;

	target_name = tab[0];
	if (tab[1] == NULL)
		return (dprintf(s->control.socket, ":%s 412 ERR_NOTEXTTOSEND"
			" :No text to send%s", irc->control.ip, ENDL), 0);
	target = get_by_session_nickname(target_name, irc->clients);
	if (target == NULL)
	return (dprintf(s->control.socket, ":%s 401 ERR_NOSUCHNICK %s "
	":No such nick/channel%s", irc->control.ip, target_name, ENDL), 0);
	asprintf(&msg, ":%s PRIVMSG %s", s->nickname, target_name);
	for (size_t i = 1; tab[i] != NULL ; ++i)
		asprintf(&msg, "%s %s", msg, tab[i]);
	asprintf(&msg, "%s%s", msg, ENDL);
	fprintf(stderr, "MESSAGE PRIVE:%s", msg);
	write_fd(target->control.socket, msg);
	free(msg);
	return (0);
}

int send_msg(t_irc *irc, t_session *session, char **tab)
{
	if (tab[0][0] == '#')
		return (write_to_channel(irc, session, tab));
	return (send_privmsg(irc, session, tab));
}

int send_privfile(t_irc *irc, t_session *session, char **tab)
{
	(void) irc;
	(void) session;
	(void) tab;
	fprintf(stderr, "Envoie de fichier non géré\n");
	return (0);
}

int privmsg_function(t_irc *irc, t_session *session, char **tab)
{
	size_t argu = count_row(tab);

	if (argu == 0)
		return (dprintf(session->control.socket,
		":%s 411 ERR_NORECIPIENT :No recipient given (PRIVMSG)%s",
		irc->control.ip, ENDL), 0);
	else if (argu >= 2 && *tab[1] == ':')
		return (send_msg(irc, session, tab));
	else if (argu == 3)
		return (send_privfile(irc, session, tab));
	return (fprintf(stderr, "Bad format.\n"), 0);
}
