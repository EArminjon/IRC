/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/05/18
*/

#include "server.h"

size_t count_character(const char *str, char filter)
{
	size_t nb = 0;

	for (size_t i = 0 ; str != NULL && str[i] != '\0' ; ++i) {
		if (str[i] == filter)
			++nb;
	}
	return (nb);
}

char **str_to_tab(char *str)
{
	char **array = NULL, *line = NULL;
	size_t i = 0, len = 1 + count_character(str, ' ');

	if (str == NULL)
		return (fprintf(stderr, "Out of memory.\n"), NULL);
	array = malloc(sizeof(char *) * (len + 1));
	if (array == NULL)
		return (fprintf(stderr, "Out of memory.\n"), NULL);
	array[0] = NULL;
	line = strsep(&str, " ");
	while (line) {
		array[i++] = strdup(line);
		line = strsep(&str, " ");
	}
	array[i] = NULL;
	return (array);
}

void **free_array(char **array)
{
	if (array == NULL)
		return NULL;
	for (size_t i = 0 ; array[i] != NULL ; ++i)
		free_secur(array[i]);
	free_secur(array);
	return (NULL);
}
