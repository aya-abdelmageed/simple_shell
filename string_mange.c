#include "shell.h"


/**
 * _putchar - writes to stdout
 * @c: The character
 * Return: 1 or -1
 */

int _putchar(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}

	if (c != BUF_FLUSH)
		buff[a++] = c;

	return (1);
}

/**
 * _puts - prints a string
 * @str: the string
 * Return: Nothing
 */

void _puts(char *str)
{
	int a;

	if (!str)
		return;

	for (a = 0; str[a] != '\0'; a++)
	{
		_putchar(str[a]);
	}
}

/**
 * _strcmp - compare between two strings.
 * @s1: the first
 * @s2: the second
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);

	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer
 */

char *_strcat(char *dest, char *src)
{
	char *ans = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (ans);
}

