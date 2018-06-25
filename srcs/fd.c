/*
** EPITECH PROJECT, 2018
** fd
** File description:
** fd
*/

#include "server.h"

char *read_fd(int fd)
{
	static char buffer[READ_SIZE];
	__ssize_t empty;

	memset(buffer, '\0', READ_SIZE);
	if (!is_valid_fd(fd))
		return NULL;
	empty = read(fd, &buffer, READ_SIZE);
	if (empty <= 0)
		return (NULL);
	return (buffer);
}

bool is_valid_fd(int fd)
{
	return (fcntl(fd, F_GETFD) != -1);
}

int close_fd(int fd)
{
	return (is_valid_fd(fd) ? close(fd) : 0);
}

int write_fd(int fd, char *str)
{
	if (!is_valid_fd(fd) || write(fd, str, strlen(str)) == -1)
		return (84);
	return (0);
}