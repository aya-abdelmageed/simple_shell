#include "shell.h"

/**
 * _history - prints the history
 * @data: for maintaining the constant function prototype.
 * Return: 0
 */
int _history(info_t *data)
{
	print_list(data->history);
	return (0);
}
