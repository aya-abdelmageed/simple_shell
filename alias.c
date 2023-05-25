#include "shell.h"

int unset_alias(info_t *data, char *str);
int _alias(info_t *data);
int print_alias(list_t *node);
int set_alias(info_t *data, char *str);

/**
 * set_alias - sets alias to the string
 * @data: struct
 * @str: string
 *
 * Return: 0 or 1
 */
int set_alias(info_t *data, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (add_node_from_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias
 * @node: node
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *c = NULL, *a = NULL;

	if (node)
	{
		c = _strchr(node->str, '=');
		for (a = node->str; a <= c; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * unset_alias - unsets alias to a string
 * @data: struct
 * @str: the string
 * Return: 0 or 1
 */
int unset_alias(info_t *data, char *str)
{
	char *s, x;
	int output;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	x = *s;
	*s = 0;
	output = delete_node_at_index(&(data->alias),
		node_index_get(data->alias, node_starts_with(data->alias, str, -1)));
	*s = x;
	return (output);
}

/**
 * _alias - manages aliases
 * @data: arguments is Using to maintain constant function prototype.
 *  Return: 0
 */
int _alias(info_t *data)
{
	int j = 1;
	char *c = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	while (data->argv[j])
	{
		c = _strchr(data->argv[j], '=');
		if (c)
			set_alias(data, data->argv[j]);
		else
			print_alias(node_starts_with(data->alias, data->argv[j], '='));
		j++;
	}

	return (0);
}
