#include "shell.h"

/**
 * print_dec - prints a decimal
 * @input: input
 * @fds: the file descriptor
 * Return: number of chars
 */
int print_dec(int input, int fds)
{
	int j, c = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int abs, curr;

	if (fds == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		abs = -input;
		__putchar('-');
		c++;
	}
	else
		abs = input;
	curr = abs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (abs / j)
		{
			__putchar('0' + curr / j);
			c++;
		}
		curr %= j;
	}

	__putchar('0' + curr);
	c++;

	return (c);
}
