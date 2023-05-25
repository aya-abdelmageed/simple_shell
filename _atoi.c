#include "shell.h"

/**
 * interactive - checks if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * _atoi - converts a string to an integer (handles negative numbers) 
 * @s: the string we're converting
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i = 0, sign = 1, flag = 0, output;
	unsigned int result = 0;
	
	while (s[i] != '\0' && flag != 2) {
		if (s[i] == '-') {
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9') {
			flag = 1;
			result = result * 10 + (s[i] - '0');
		} else if (flag == 1) {
			flag = 2;
		}

		i++;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * check_delim - checks if character is a delimeter
 * @c: the char we're checking
 * @delim: the delimeter string to check against
 * Return: 1 if true, 0 if false
 */
int check_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks alphabetic character
 * @c: The character we're checking
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

