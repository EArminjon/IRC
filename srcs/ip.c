/*
** EPITECH PROJECT, 2018
** ip
** File description:
** ip
*/

#include "server.h"

bool valid_digit(char *ip_str)
{
	if (ip_str == NULL)
		return (false);
	while (*ip_str) {
		if (*ip_str >= '0' && *ip_str <= '9')
			++ip_str;
		else
			return (false);
	}
	return (true);
}

bool check_ip(char *ip)
{
	int num, dots = 0;
	char *ptr = NULL;

	if (ip == NULL)
		return (false);
	ptr = strtok(ip, ".");
	if (ptr == NULL)
		return (false);
	while (ptr) {
		if (!valid_digit(ptr))
			return (false);
		num = atoi(ptr);
		if (num >= 0 && num <= 255) {
			ptr = strtok(NULL, ".");
			if (ptr != NULL)
			++dots;
		} else
			return (false);
	}
	return (dots != 3 ? false : true);
}
