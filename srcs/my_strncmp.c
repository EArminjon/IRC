/*
** EPITECH PROJECT, 2018
** dd
** File description:
** dd
*/

#include <stdlib.h>

int my_strncmp(char *s1, char *s2, size_t len)
{
	size_t i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && i < len && s1[i] != '\0' && s2[i] != '\0')
		++i;
	if (s1[i] == '\0' && (s2[i] == '\0' || s2[i] == ' '
			|| s2[i] == '\r' || s2[i] == '\n'))
		return (0);
	else if (s2[i] == '\0' && (s1[i] == '\0' || s1[i] == ' '
			|| s1[i] == '\r' || s1[i] == '\n'))
		return (0);
	return (s1[i] - s2[i]);
}
