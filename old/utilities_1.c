#include "header_shell.h"

/**
 * _atoi - creates integer from string
 * @str: char pointer
 * Return: new number
 */
int _atoi(char *str)
{
	int i, total = 0;

	if (str == NULL)
		return (0);

	for (i = 0; str[i]; i++)
	{
		total *= 10;
		total += (str[i] - 48);
	}

	return (total);
}


/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * @fd: either stdout or stderr
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 * _strcat - concatenates two strings with a seperator
 * @left: input string 1
 * @right: input string 2
 * @sep: char to sandwhich between left and right
 *
 * Return: pointer to new string in memory
 */
char *_strcat(char *left, char *right, char sep)
{
	char *out;
	int i = 0, j = 0, k;

	/* get length of left string */
	while (left[i])
		i++;
	/* get length of right string */
	while (right[j])
		j++;
	/* malloc new string */
	out = malloc(sizeof(char) * (i + j + 2));
	if (out == NULL)
		return (NULL);
	/* set left chars */
	for (k = 0; k < i; k++)
		out[k] = left[k];
	/* for our purposes, we separate left and right with a forward slash */
	out[i++] = sep;
	/* set right chars */
	for (k = 0; k < j; k++)
		out[i + k] = right[k];
	/* c strings end in a null byte */
	out[i + k] = '\0';
	return (out);
}


/**
 * _strcmp - compares two strings ASCII values and returns result
 * @s1: pointer to input string 1
 * @s2: pointer to input string 2
 *
 * Return: numerical difference of most recent dissimilar character, else zero
 */
int _strcmp(char *s1, char *s2)
{
	int result = 0;
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (result == 0 && s1[i] && s2[i])
	{
		result = s1[i] - s2[i];
		i++;
	}

	if (result == 0)
		result = s1[i] - s2[i];

	return (result);
}
