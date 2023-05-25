#include "shell.h"


/**
 * print_list - to print all elements of a linked list
 * @h: pointer
 * Return: size
 */

size_t print_list(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		len++;
	}

	return (len);
}

/**
 * print_list_str - to print the str element of a linked list
 * @h: pointer
 * Return: size
 */

size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * list_len - to determine the length of a linked list
 * @h: pointer
 * Return: length
 */

size_t list_len(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		h = h->next;
		l++;
	}

	return (l);
}
