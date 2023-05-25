#include "shell.h"

/**
 * print_error - if an error occurs, prints the error message
 * @data: Structure containing potential arguments. Used to maintain 
 * @estr: type of error that occured as a string
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *data, char *estr)
{
	_eputs(data->fname);
	_eputs(": ");
	print_dec(data->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(data->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
