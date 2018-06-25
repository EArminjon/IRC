/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/05/18
*/

#include <stdlib.h>

void *free_secur(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	return (NULL);
}