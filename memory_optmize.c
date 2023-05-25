#include "shell.h"

/**
 * free_pointer - frees a pointer
 * @ptr: address
 * Return: 1 otherwise 0.
 */
int free_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}
