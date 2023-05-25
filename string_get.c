#include "shell.h"


/**
 * _strdup - duplicates a string
 * @str: the string
 * Return: pointer to the result string
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *ans;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;
	ans = malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);

	for (len++; len--;)
		ans[len] = *--str;

	return (ans);
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer
 */

char *_strcpy(char *dest, char *src)
{
	int j;

	if (dest == src || src == 0)
		return (dest);

	for (j = 0; src[j]; j++)
	{
		dest[j] = src[j];
	}
	dest[j] = 0;

	return (dest);
}

/**
 * _strlen - get length
 * @s: the string
 * Return: length of the string
 */

int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;

	return (a);
}

/**
 * starts_with - checks if the string needle starts with the substring haystack
 * @haystack: string
 * @needle: substring
 * Return: address
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}
