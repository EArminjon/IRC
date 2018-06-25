/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/05/18
*/
#ifndef IRC_CLIENT_H
#define IRC_CLIENT_H
#include "irc.h"
typedef struct s_client {
	t_com control;
	t_com transfert;
	fd_set readfds;
	char *nickname;
} t_client;

typedef struct s_client_pointer_cmd {
	char *name;
	size_t size;
	int (*ptr_function)(t_client *client, char *buf);
} t_client_pointer_cmd;
char *read_fd(int fd);
#endif //IRC_CLIENT_H
