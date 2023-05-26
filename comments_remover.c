#include "shell.h"


/**
 * comments_remover - replaces the first '#' character with '\0' 
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void comments_remover(char *buf)
{
	int i;

for (i = 0; buf[i] != '\0'; i++)
{
	if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
	{
		buf[i] = '\0';
		break;
	}
}
}
