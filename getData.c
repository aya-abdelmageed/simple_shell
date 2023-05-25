#include "shell.h"


/**
 * set_data - struct initializer for info_t
 * @info: struct address
 * @av: argument vector
 */
void set_data(info_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = string_split(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replace_alias(data);
		replace_vars(data);
	}
}

/**
 * data_clear - initializes data_t struct
 * @data: struct address
 */
void data_clear(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_data - frees data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void free_data(info_t *data, int all)
{
	ffree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list_nodes(&(data->env));
		if (data->history)
			free_list_nodes(&(data->history));
		if (data->alias)
			free_list_nodes(&(data->alias));
		ffree(data->environ);
			data->environ = NULL;
		free_pointer((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}
