#include "shell.h"



/**
 * _mysetenv - sets an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _mysetenv(info_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return 0;
	return 1;
}

/**
 * _getenv - gets the value of an environ variable
 * @data: Structure containing potential arguments. Used to maintain
 * @env_name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *data, const char *env_name)
{
	list_t *node = data->env;
	char *c;

	for (; node; node = node->next)
	{
c = starts_with(node->str, env_name);
		if (c && *c)
			return c;
	}
	return NULL;
}

/**
 * join_env_list - joins a list of strings into a single string 
 * @data: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
int join_env_list(info_t *data)
{
	list_t *node = NULL;
	size_t i = 0;

	while (environ[i])
	{
		add_node_from_end(&node, environ[i], 0);
		i++;
	}
	data->env = node;
	return 0;
}

/**
 * _myunsetenv - deletes an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
int _myunsetenv(info_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return 1;
	}
	for (i = 1; i < data->argc; i++)
		_unsetenv(data, data->argv[i]);

	return 0;
}

/**
 * _env - shows the current environment
 * @data: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
int _env(info_t *data)
{
	print_list_str(data->env);
	return 0;
}
