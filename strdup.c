#include "header_shell.h"
/**
 * _strdup - creates a copy of str in a new c string and returns a pointer
 * @str: string to be copied
 *
 * Return: pointer to new string, or NULL of str is NULL or malloc fails
 */
char *_strdup(char *str)
{
	int length = 0;
	int i = 0;
	char *p;
	if (str == NULL)
		return (NULL);
	while (str[length])
		length++;
	p = (char *)malloc(sizeof(char) * (length + 1));
	if (p == NULL)
		return (NULL);
	while (i <= length)
	{
		p[i] = str[i];
		i++;
	}
	return (p);
}
