#include "shell.h"


/**
 * delete_node_at_index - deletes node
 * @head: address
 * @index: index
 * Return: 1 or 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int j = 0;
	list_t *nd, *prev_nd;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *head;

	while (nd)
	{
		if (j == index)
		{
			prev_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		j++;
		prev_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * add_node - to add a node to the begin of the list
 * @head: address of pointer
 * @str: string
 * @num: node index
 * Return: size
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *node_h;

	if (!head)
		return (NULL);

	node_h = malloc(sizeof(list_t));
	if (!node_h)
		return (NULL);

	_memset((void *)node_h, 0, sizeof(list_t));
	node_h->num = num;

	if (str)
	{
		node_h->str = _strdup(str);
		if (!node_h->str)
		{
			free(node_h);
			return (NULL);
		}
	}
	node_h->next = *head;
	*head = node_h;

	return (node_h);
}

/**
 * add_node_from_end - to add a node to the end
 * @head: address of pointer
 * @str: string
 * @num: node index
 * Return: size
 */

list_t *add_node_from_end(list_t **head, const char *str, int num)
{
	list_t *new_n, *n;

	if (!head)
		return (NULL);

	n = *head;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	_memset((void *)new_n, 0, sizeof(list_t));
	new_n->num = num;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = new_n;
	}
	else
		*head = new_n;
	return (new_n);
}
