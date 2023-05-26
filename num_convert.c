#include "shell.h"


/**
 * num_convert - converts a number to any base
 * @num: number
 * @base: base
 * @flags: flags to determine if uppercase or lowercase
 *
 * Return: string
 */
char *num_convert(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
    
	for (; n != 0; n /= base)
		{
		*--ptr = array[n % base];
		}

	if (sign)
		*--ptr = sign;
	return ptr;
}
