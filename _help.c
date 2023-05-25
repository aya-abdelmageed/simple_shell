#include "shell.h"

/**
 * _help - displays the help page
 * @data: to maintain constant function prototype.
 * Return: 0
 */
int _help(info_t *data)
{
	char **arguments;

	arguments = data->argv;

	_puts("help call works. Function not yet implemented \n");

	if (0)
		_puts(*arguments);

	return (0);
}
