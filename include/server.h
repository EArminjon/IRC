/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/05/18
*/

#ifndef IRC_SERVER_H
#define IRC_SERVER_H
#include "irc.h"
typedef struct s_member {
	char *nickname;
	int fd;
} t_member;
typedef struct s_channel {
	char *name;
	char *owner;
	t_list *members;
} t_channel;

typedef struct s_ping {
	bool enable;
	time_t time;
} t_ping;

typedef struct s_session {
	t_com control;
	char *nickname;
	char *username;
	char *host;
	char *server;
	char *realname;
	t_list *channels;
	t_ping ping;
	bool connected;
} t_session;

enum t_fileState {
	NONE,
	WAITING,
	ACCEPTED,
	DENIED
};

typedef struct s_file {
	char *name;
	char *owner;
	char *target;
	enum t_fileState state;
} t_file;

typedef struct s_irc {
	t_com control;
	t_list *clients;
	t_list *channels;
	size_t nb_client;
	fd_set readfds;
	t_list *files;
} t_irc;

typedef struct s_server_pointer_cmd {
	char *name;
	const size_t size;
	int (*ptr_function)(t_irc *irc, t_session *session, char **tab);
	bool required_connecion;
} t_server_pointer_cmd;
char *get_by_channel_name(char *name, t_list *list);
t_member *get_by_member_name(char *name, t_list *list);
t_session *get_by_session_nickname(char *name, t_list *list);
t_channel *get_by_channel_by_name(char *name, t_list *list);
bool delete_if_member(void *data, t_list *list);
void stop_ping(t_session *session);
bool is_ping_fail(t_session *session);
int send_ping_request(t_session *session, t_irc *irc);
/* CHANNEL */
int leave_channel(t_irc *irc, t_session *session, char *name);
int join_channel(t_irc *irc, t_session *session, char *name);
int remove_all_channels(t_irc *irc);
int manage_client(t_irc *irc, t_session *session);
int init_read(t_irc *irc);
int read_server(t_irc *irc);
/* CLIENT */
int add_client(t_irc *irc);
int remove_client(t_irc *irc, t_session *session);
int remove_all_clients(t_irc *irc);
void init_network(t_session *session, int fd, struct sockaddr_in *client,
			t_irc *irc);
void init_client(t_session *session);
/* FILES */
void init_file(t_file *file);
int remove_file(t_irc *irc, t_file *file);
int remove_all_files(t_irc *irc);
/* SERVER */
int quit_function(t_irc *irc, t_session *session, char **tab);
int pong_function(t_irc *irc, t_session *session, char **tab);
int ping_function(t_irc *irc, t_session *session, char **tab);
int part_function(t_irc *irc, t_session *session, char **tab);
int join_function(t_irc *irc, t_session *session, char **tab);
int user_function(t_irc *irc, t_session *session, char **tab);
int users_function(t_irc *irc, t_session *session, char **tab);
int nick_function(t_irc *irc, t_session *session, char **tab);
int privmsg_function(t_irc *irc, t_session *session, char **tab);
void send_to_channel(t_session *session, t_channel *channel, char *m, bool f);
void edit_channel(t_irc *irc, t_session *session, char *str);
int write_to_channel(t_irc *irc, t_session *session, char **tab);
size_t count_row(char **tab);
int names_function(t_irc *irc, t_session *session, char **tab);
int remove_server(t_irc *irc);
int read_clients(t_irc *irc);
int server(int port);
void send_to_all(t_irc *irc, t_session *session, char *msg, bool filter);
void init_channel(t_channel *channel, char *name, char *owner);
int add_channel(t_irc *irc, char *name, char *owner);
void init_member(t_member *member, t_session *session);

#endif //IRC_SERVER_H
