#include "shell.h"



/**
 * _setenv - sets an environment variable and creates it if it doesn't exist
 * @data: Structure containing potential arguments. Used to maintain
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = data->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_from_end(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return 0;
}

/**
 * _unsetenv - deletes an environment variable
 * @data: Structure containing potential arguments. Used to maintain
  * @var: the string env var property
 *  Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * get_environ - gets the value of an environ variable
 * @data: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
char **get_environ(info_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = convert_list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}
