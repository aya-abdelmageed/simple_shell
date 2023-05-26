#include "shell.h"

/**
 * history_build_list - for adding to the history linked list
 * @data: argu to maintain
 * @buf: the buffer
 * @linecount: linecount and histcount
 * Return: 0
 */
int history_build_list(info_t *data, char *buf, int linecount)
{
	list_t *p = NULL;

	if (data->history)
		p = data->history;
	add_node_from_end(&p, buf, linecount);

	if (!data->history)
		data->history = p;
	return (0);
}

/**
 * history_writes - creates or appends file
 * @data: struct
 * Return: 1 or -1
 */
int history_writes(info_t *data)
{
	ssize_t d;
	char *file_name = get_history_of_file(data);
	list_t *p = NULL;

	if (!file_name)
		return (-1);

	d = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (d == -1)
		return (-1);
	for (p = data->history; p; p = p->next)
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
 * @data: struct
 * Return: histcount or 0
 */
int history_reads(info_t *data)
{
	int j, end = 0, linecount = 0;
	ssize_t d, rdlen, size = 0;
	struct stat s;
	char *buff = NULL, *file_name = get_history_of_file(data);

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
			history_build_list(data, buff + end, linecount++);
			end = j + 1;
		}
	if (end != j)
		history_build_list(data, buff + end, linecount++);
	free(buff);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data->history), 0);
	recount_history(data);
	return (data->histcount);
}

/**
 * recount_history - recount the history linked list
 * @data: to maintain
 * Return: new histcount
 */
int recount_history(info_t *data)
{
	list_t *nd = data->history;
	int j = 0;

	while (nd)
	{
		nd->num = j++;
		nd = nd->next;
	}
	return (data->histcount = j);
}

/**
 * get_history_of_file - gets the history
 * @data: struct
 * Return: string pointer
 */

char *get_history_of_file(info_t *data)
{
	char *buff, *d;

	d = _getenv(data, "HOME=");

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
