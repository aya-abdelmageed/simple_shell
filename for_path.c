#include "shell.h"


/**
 * path_finder - to find cmd in the PATH
 * @info: struct for info
 * @pathstr: the PATH
 * @cmd: the cmd
 * Return: full path of cmd if found or NULL
 */

char *path_finder(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (check_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = char_duplicates(pathstr, curr, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (check_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr = j;
		}
		j++;
	}
	return (NULL);
}

/**
 * char_duplicates - duplicates chars
 * @pathstr: the PATH
 * @start: index
 * @stop: index
 * Return: pointer
 */

char *char_duplicates(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int j = 0, x = 0;

	for (x = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buff[x++] = pathstr[j];
	buff[x] = 0;
	return (buff);
}

/**
 * check_cmd - executable command or not
 * @info: struct
 * @path: path
 * Return: 1 or 0
 */

int check_cmd(info_t *info, char *path)
{
	struct stat s;

	(void)info;

	if (!path || stat(path, &s))
		return (0);


	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

