#include "shell.h"

/**
 * **string_split - splits it into words and ignore repeat delimiters.
 * @str: string
 * @d: the delimeter
 * Return: a pointer or NULL
 */

char **string_split(char *str, char *d)
{
	int a, count_words = 0, b, x, m;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";

	for (a = 0; str[a] != '\0'; a++)
		if (!check_delim(str[a], d) && (check_delim(str[a + 1], d) || !str[a + 1]))
			count_words++;

	if (count_words == 0)
		return (NULL);
	c = malloc((1 + count_words) * sizeof(char *));
	if (!c)
		return (NULL);

	for (a = 0, b = 0; b < count_words; b++)
	{
		while (check_delim(str[a], d))
			a++;
		x = 0;

		while (!check_delim(str[a + x], d) && str[a + x])
			x++;
		c[b] = malloc((x + 1) * sizeof(char));

		if (!c[b])
		{
			for (x = 0; x < b; x++)
				free(c[x]);
			free(c);
			return (NULL);
		}

		for (m = 0; m < x; m++)
			c[b][m] = str[a++];
		c[b][m] = 0;
	}
	c[b] = NULL;

	return (c);
}

/**
 * **split_string - for splitting the string
 * @str: string
 * @d: the delimeter
 * Return: a pointer or NULL
 */
char **split_string(char *str, char d)
{
	int a, count_words = 0, b, x, m;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			count_words++;

	if (count_words == 0)
		return (NULL);

	c = malloc((1 + count_words) * sizeof(char *));
	if (!c)
		return (NULL);

	for (a = 0, b = 0; b < count_words; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		x = 0;
		while (str[a + x] != d && str[a + x] && str[a + x] != d)
			x++;
		c[b] = malloc((x + 1) * sizeof(char));
		if (!c[b])
		{
			for (x = 0; x < b; x++)
				free(c[x]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < x; m++)
			c[b][m] = str[a++];
		c[b][m] = 0;
	}
	c[b] = NULL;

	return (c);
}
