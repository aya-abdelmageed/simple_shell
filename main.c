#include "shell.h"

/**
 * main - our main fun
 * @ac: arg counter
 * @av: arg vector
 * Return: 0 or 1
 */

int main(int ac, char **av)
{
	int f = 2;
	info_t data[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = f;
	}

	join_env_list(data);
	history_reads(data);
	shell_loop(data, av);

	return (EXIT_SUCCESS);
}
