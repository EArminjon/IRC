/*
** EPITECH PROJECT, 2018
** join_part
** File description:
** join_part
*/

#include "server.h"

int join_function(t_irc *irc, t_session *s, char **tab)
{
	int res = 0;
	char *channelname = NULL, *msg = NULL;

	dprintf(s->control.socket, ":%s JOIN :%s%s", s->nickname, tab[0], ENDL);
	if (tab[0] == NULL)
		return (dprintf(s->control.socket, ":%s 461 ERR_NEEDMOREPARAMS"
		" PART :Not enough parameters%s", irc->control.ip, ENDL), 0);
	channelname = get_by_channel_name(tab[0], s->channels);
	if (channelname == NULL)
		res = join_channel(irc, s, tab[0]);
	dprintf(s->control.socket, ":%s 331 RPL_NOTOPIC %s :%s",
		irc->control.ip, tab[0], ENDL);
	names_function(irc, s, tab);
	asprintf(&msg, ":%s JOIN :%s%s", s->nickname, tab[0], ENDL);
	send_to_channel(s, get_by_channel_by_name(tab[0], irc->channels),
			msg, true);
	free_secur(msg);
	return (res);
}

int part_all_function(t_session *s, t_channel *c, int res)
{
	char *msg = NULL;

	asprintf(&msg, ":%s PART %s%s", s->nickname, c->name, ENDL);
	send_to_channel(s, c, msg, true);
	return (free_secur(msg), res);
}

int part_function(t_irc *i, t_session *s, char **tab)
{
	char *channelname = NULL;
	int res;
	t_channel *c = NULL;

	dprintf(s->control.socket, ":%s PART %s%s", s->nickname, tab[0], ENDL);
	if (tab[0] == NULL || *tab[0] == '\0')
		return (dprintf(s->control.socket, ":%s 461 ERR_NEEDMOREPARAMS"
		" PART :Not enough parameters%s", i->control.ip, ENDL), 0);
	channelname = get_by_channel_name(tab[0], s->channels);
	if (channelname == NULL)
	return (dprintf(s->control.socket, ":%s 442 ERR_NOTONCHANNEL "
	"%s :You're not on that channel%s", i->control.ip, tab[0], ENDL), 0);
	res = leave_channel(i, s, tab[0]);
	if (res == -1)
		return (dprintf(s->control.socket, ":%s 403 ERR_NOSUCHCHANNEL"
		" %s :No such channel%s", i->control.ip, tab[0], ENDL), 0);
	c = get_by_channel_by_name(tab[0], i->channels);
	if (!c)
		return (res);
	return (part_all_function(s, c, res));
}
