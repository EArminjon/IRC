/*
** EPITECH PROJECT, 2018
** add_remove
** File description:
** add_remove
*/

#include "server.h"

int list_function(t_irc *irc, t_session *session, char **tab)
{
	t_node *c;
	t_channel *channel;
	char *target = tab[0] == NULL ? "\0" : tab[0];

	dprintf(session->control.socket, ":%s 321 RPL_LISTSTART Channel :User"
		"s Name%s", irc->control.ip, ENDL);
	if (irc->channels != NULL) {
		for (c = irc->channels->head; c != NULL ; c = c->next) {
			channel = (t_channel *) c->data;
			if (strstr(channel->name, target) != NULL)
			dprintf(session->control.socket, ":%s 322 RPL_LIST %s "
			":%s", irc->control.ip, channel->name, ENDL);
		}
	}
	dprintf(session->control.socket, ":%s 323 RPL_LISTEND :End of /L"
		"IST%s", irc->control.ip, ENDL);
	return (0);
}

int write_to_channel(t_irc *irc, t_session *s, char **tab)
{
	char *msg = NULL;
	t_channel *channel = NULL;

	if (count(s->channels) == 0)
		return (dprintf(s->control.socket, ":%s 401 ERR_NOSUCHNICK :No"
			" such channel%s", irc->control.ip, ENDL), 0);
	channel = get_by_channel_by_name(tab[0], irc->channels);
	if (channel == NULL)
		return (dprintf(s->control.socket, ":%s 401 ERR_NOSUCHNICK %s"
		" :No such channel%s", irc->control.ip, &tab[0][1], ENDL), 0);
	asprintf(&msg, ":%s PRIVMSG %s", s->nickname, channel->name);
	for (size_t i = 1 ; tab[i] != NULL ; ++i)
		asprintf(&msg, "%s %s", msg, tab[i]);
	asprintf(&msg, "%s%s", msg, ENDL);
	send_to_channel(s, channel, msg, true);
	free(msg);
	return (0);
}

t_server_pointer_cmd *get_command(void)
{
	static t_server_pointer_cmd c[] = {
		{"NICK", strlen("NICK"), nick_function, false},
		{"USER", strlen("USER"), user_function, false},
		{"LIST", strlen("LIST"), list_function, true},
		{"JOIN", strlen("JOIN"), join_function, true},
		{"PART", strlen("PART"), part_function, true},
		{"USERS", strlen("USERS"), users_function, true},
		{"NAMES", strlen("NAMES"), names_function, true},
		{"PRIVMSG", strlen("PRIVMSG"), privmsg_function, true},
		{"PONG", strlen("PONG"), pong_function, false},
		{"PING", strlen("PING"), ping_function, false},
		{"QUIT", strlen("QUIT"), quit_function, false}};
	return (c);
}

int manage_command(t_irc *irc, t_session *session, char **tab)
{
	const size_t nb = 11;
	t_server_pointer_cmd *c = get_command();

	session->ping.time = time(NULL);
	for (size_t i = 0 ; i < nb ; ++i)
		if (my_strncmp(tab[0], c[i].name, c[i].size) == 0) {
			if (c[i].required_connecion == true &&
			session->connected == false)
			return (dprintf(session->control.socket,
			"300 RPL_NONE%s", ENDL), 0);
			return (c[i].ptr_function(irc, session, &tab[1]));
		}
	return (dprintf(session->control.socket, "300 RPL_NONE%s", ENDL), 0);
}

int manage_client(t_irc *irc, t_session *session)
{
	char *buffer = NULL, *cmd = NULL, **array = NULL;

	if (!is_valid_fd(session->control.socket))
		return (remove_client(irc, session), 1);
	buffer = read_fd(session->control.socket);
	if (buffer == NULL)
		return (remove_client(irc, session), 1);
	cmd = strtok(buffer, ENDL);
	while (cmd && !my_break(false)) {
		printf("CMD:%s\n", cmd);
		array = str_to_tab(cmd);
		if (array == NULL)
			return (84);
		if (manage_command(irc, session, array) == 1)
			return (1);
		free_array(array);
		cmd = strtok(NULL, ENDL);
	}
	return (0);
}
