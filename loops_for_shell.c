#include "shell.h"


/**
 * builtin_finder - finds a command
 * @data: data struct
 * Return: -1 if not found, 0 if executed successfully,
 * 1 found but not successful, 2 if exit()
 */

int builtin_finder(info_t *data)
{
	int j = 0, builtin_ret = -1;
	builtin_table builtin_tbl[] = {
		{"exit", _myexit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	while (builtin_tbl[j].type)
	{
		if (_strcmp(data->argv[0], builtin_tbl[j].type) == 0)
		{
			data->line_count++;
			builtin_ret = builtin_tbl[j].func(data);
			break;
		}
		j++;
	}
	return (builtin_ret);
}

/**
 * cmd_fork - forks
 * @data: data struct
 * Return: void
 */

void cmd_fork(info_t *data)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}

	if (childPid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}

	else
	{
		wait(&(data->status));

		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

/**
 * cmd_finder - for finding a command
 * @data: struct
 * Return: void
 */

void cmd_finder(info_t *data)
{
	int j, x;
	char *path = NULL;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}

	for (j = 0, x = 0; data->arg[j]; j++)
		if (!check_delim(data->arg[j], " \t\n"))
			x++;
	if (!x)
		return;


	path = path_finder(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		cmd_fork(data);
	}

	else
	{
		if ((interactive(data) || _getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && check_cmd(data, data->argv[0]))
			cmd_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * shell_loop - shell loop
 * @data: struct
 * @av: vector
 * Return: 0 or 1
 */
int shell_loop(info_t *data, char **av)
{
	ssize_t s = 0;
	int ret = 0;

	while (s != -1 && ret != -2)
	{
		data_clear(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(data);

		if (s != -1)
		{
			set_data(data, av);
			ret = builtin_finder(data);
			if (ret == -1)
				cmd_finder(data);
		}

		else if (interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	history_writes(data);
	free_data(data, 1);

	if (!interactive(data) && data->status)
		exit(data->status);

	if (ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}

	return (ret);
}
