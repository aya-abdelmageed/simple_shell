#include "shell.h"


/**
 * _myexit - exits the shell with a given exit status
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if data.argv[0] != "exit"
 */
int _myexit(info_t *data)
{
	int checkExit;

	if (data->argv[1]) /* If there is an exit arguement */
	{
		checkExit = _atoierr(data->argv[1]);
		if (checkExit == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return 1;
		}
		data->err_num = _atoierr(data->argv[1]);
		return -2;
	}
	data->err_num = -1;
	return -2;
}
