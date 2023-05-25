#include "shell.h"


/**
 * convert_list_to_strings - from list to strings
 * @head: pointer
 * Return: strings
 */

char **convert_list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t l = list_len(head), i;
	char **strs;
	char *str;

	if (!head || !l)
		return (NULL);

	strs = malloc(sizeof(char *) * (l + 1));
	if (!strs)
		return (NULL);

	for (l = 0; nd; nd = nd->next, l++)
	{
		str = malloc(_strlen(nd->str) + 1);
		if (!str)
		{
			for (i = 0; i < l; i++)
				free(strs[i]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nd->str);
		strs[l] = str;
	}
	strs[l] = NULL;

	return (strs);
}

/**
 * free_list_nodes - to free all nodes
 * @head_ptr: address of pointer
 * Return: nothing
 */
void free_list_nodes(list_t **head_ptr)
{
	list_t *head, *nd, *next_nd;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nd = head;
	while (nd)
	{
		next_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = next_nd;
	}

	*head_ptr = NULL;
}
