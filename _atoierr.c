#include "shell.h"

/**
 * _atoierr - converts a string to an integer and checks for errors 
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _atoierr(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (result);
}
