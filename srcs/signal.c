/*
** EPITECH PROJECT, 2018
** signal
** File description:
** signal
*/

#include "server.h"

bool my_break(bool state)
{
	static bool stop = false;

	if (state == true)
		stop = state;
	return (stop);
}

void my_handler(int s)
{
	if (s == SIGINT)
		my_break(true);
	else
		fprintf(stderr, "SigPipe\n");
}

int my_signal(void)
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	sigaction(SIGPIPE, &sigIntHandler, NULL);
	return 0;
}
