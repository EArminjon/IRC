/*
** EPITECH PROJECT, 2018
** irc
** File description:
** irc
*/

#ifndef MY_IRC_H_
#define MY_IRC_H_
#define _GNU_SOURCE
#include <fcntl.h>
#include <netdb.h>
#include <memory.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
/* PART I: STRUCT */
typedef struct s_node {
	void *data;
	struct s_node *next;
} t_node;

typedef struct s_list {
	t_node *head;
} t_list;

typedef struct s_com {
	char *ip;
	int socket;
	int port;
	struct sockaddr_in s_in;
} t_com;

/* PART II: LINKED LIST FUNCTONS */
t_list *emptyt_list(void);
size_t count(t_list *list);
void add(void *data, t_list *list);
void delete(void *data, t_list *list);
/* PART III: FUNCTIONS */
char *read_fd(int fd);
int my_strncmp(char *s1, char *s2, size_t len);
size_t count_character(const char *str, char filter);
char **str_to_tab(char *str);
void **free_array(char **array);
void *free_secur(void *ptr);
bool check_ip(char *ip);
bool is_valid_fd(int fd);
int close_fd(int fd);
bool my_break(bool state);
int my_signal(void);
bool connect_socket(t_com *com, char *proto_name);
bool create_socket(t_com *chanel, char *proto_name);
int write_fd(int fd, char *str);
/* PART 6: MACCRO */
#define ENDL "\r\n"
#define READ_SIZE 1024
#endif /* !MY_IRC_H_ */
