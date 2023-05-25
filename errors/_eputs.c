#include "shell.h"


/**
 * _eputchar - writes the character c to stderr and flushes the buffer
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return 0;
}

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
	_eputchar(str[i]);
}
