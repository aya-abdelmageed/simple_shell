#include "shell.h"

/**
 * history_build_list - for adding to the history linked list
 * @info: argu to maintain
 * @buf: the buffer
 * @linecount: linecount and histcount
 * Return: 0
 */
int history_build_list(info_t *info, char *buf, int linecount)
{
	list_t *p = NULL;

	if (info->history)
		p = info->history;
	add_node_from_end(&p, buf, linecount);

	if (!info->history)
		info->history = p;
	return (0);
}

/**
 * history_writes - creates or appends file
 * @info: struct
 * Return: 1 or -1
 */
int history_writes(info_t *info)
{
	ssize_t d;
	char *file_name = get_history_file(info);
	list_t *p = NULL;

	if (!file_name)
		return (-1);

	d = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (d == -1)
		return (-1);
	for (p = info->history; p; p = p->next)
	{
		_putsfd(p->str, d);
		_putfd('\n', d);
	}
	_putfd(BUF_FLUSH, d);
	close(d);
	return (1);
}

/**
 * history_reads - for reading from file
 * @info: struct
 * Return: histcount or 0
 */
int history_reads(info_t *info)
{
	int j, end = 0, linecount = 0;
	ssize_t d, rdlen, size = 0;
	struct stat s;
	char *buff = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	d = open(file_name, O_RDONLY);
	free(file_name);
	if (d == -1)
		return (0);
	if (!fstat(d, &s))
		size = s.st_size;
	if (size < 2)
		return (0);
	buff = malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (0);
	rdlen = read(d, buff, size);
	buff[size] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(d);
	for (j = 0; j < size; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			history_build_list(info, buff + end, linecount++);
			end = j + 1;
		}
	if (end != j)
		history_build_list(info, buff + end, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	recount_history(info);
	return (info->histcount);
}

/**
 * recount_history - recount the history linked list
 * @info: to maintain
 * Return: new histcount
 */
int recount_history(info_t *info)
{
	list_t *nd = info->history;
	int j = 0;

	while (nd)
	{
		nd->num = j++;
		nd = nd->next;
	}
	return (info->histcount = j);
}

/**
 * get_history_of_file - gets the history
 * @info: struct
 * Return: string pointer
 */

char *get_history_of_file(info_t *info)
{
	char *buff, *d;

	d = _getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	buff = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);

	buff[0] = 0;

	_strcpy(buff, d);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);

	return (buff);
}
