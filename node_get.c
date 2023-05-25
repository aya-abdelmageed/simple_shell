#include "shell.h"


/**
 * node_index_get - to get the index of specific node
 * @head: pointer
 * @node: pointer
 * Return: index or -1
 */

ssize_t node_index_get(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}

	return (-1);
}

/**
 * node_starts_with - to get a node whose string starts with prefix
 * @node: pointer
 * @prefix: string
 * @c: the next char after the prefix
 * Return: node or NULL
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pr = NULL;

	while (node)
	{
		pr = starts_with(node->str, prefix);
		if (pr && ((c == -1) || (*pr == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}
