#include "shell.h"

/**
 * _putsfd - for printing
 * @str: string
 * @fds: file descriptor
 * Return: number of chars
 */
int _putsfd(char *str, int fds)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str)
	{
		j += _putfd(*str++, fds);
	}

	return (1);
}

/**
 * _putfd - for writing char c to fds
 * @c: The character to print
 * @fds: The file descriptor
 * Return: 1 or -1
 */
int _putfd(char c, int fds)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fds, buff, j);
		j = 0;
	}

	if (c != BUF_FLUSH)
		buff[j++] = c;

	return (1);
}
