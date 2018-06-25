/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (fprintf(stderr, "Server need a port agument.\n"), 84);
	if (av[1] != NULL && (strcmp(av[1], "--help") == 0))
		return (printf("USAGE: ./server port\n"), 84);
	return (server(atoi(av[1])));
}
