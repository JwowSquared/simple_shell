#include "header_shell.h"
/**
* exit_shell - cleans up memory and exits program with status
* @t: token with arguments
* @buffer: buffer to free
* @envc: environment variables to free
*
* Return: always 1, but should never return
*/
int exit_shell(token *t, char **buffer, char ***envc)
{
	int status = _atoi(t->arguments[1]);

	free(*buffer);
	free_token(t);
	free_aos(envc, 0);
	exit(status);

	return (1);
}

/**
* env_shell - prints environment variables
* @t: not needed in this function
* @buffer: not needed in this function
* @envc: environment variables to print
*
* Return: always 1
*/
int env_shell(token *t, char **buffer, char ***envc)
{
	int i;

	(void)t;
	(void)buffer;

	for (i = 0; (*envc)[i]; i++)
	{
		print_string((*envc)[i]);
		_putchar('\n');
	}

	return (1);
}

/**
* setenv_shell - updates env on match, else create new env
* @t: token with arguments
* @buffer: not needed in this function
* @envc: environment variables
*
* Return: always 1
*/
int setenv_shell(token *t, char **buffer, char ***envc)
{
	int i;

	(void)buffer;

	if (t->argc != 3)
	{
		perror("Usage: setenv [VARIABLE] [VALUE]");
		return (1);
	}

	i = findenvi(t->arguments[1], *envc);
	if (i == -1)
		*envc = copy_aos(envc, _strcat(t->arguments[1], t->arguments[2], '='));
	else
		update_env(t->arguments[1], t->arguments[2], envc);

	return (1);
}

/**
* findenvi - finds index of key in envc
* @key: key to match with
* @envc: environment variables
*
* Return: index of env in envc, else -1
*/
int findenvi(char *key, char **envc)
{
	int i = 0, j = 0;

	while (envc[i])
	{
		while (key[j])
		{
			if (key[j] != envc[i][j])
				break;
			j++;
		}
		if (key[j] == '\0')
			return (i);
		i++;
	}
	/* return -1 if key doesn't exist in envc */
	return (-1);
}

/**
* unsetenv_shell - deletes env in envc
* @t: token of arguments
* @buffer: unused in this function
* @envc: environment variables
*
* Return: always 1
*/
int unsetenv_shell(token *t, char **buffer, char ***envc)
{
	int i;

	(void)buffer;

	if (t->argc != 2)
	{
		perror("Usage: unsetenv [VARIABLE]");
		return (1);
	}

	i = findenvi(t->arguments[1], *envc);
	if (i == -1)
		return (1);

	free((*envc)[i]);
	(*envc)[i] = (*envc)[i + 1];
	i++;
	while ((*envc)[i])
	{
		(*envc)[i] = (*envc)[i + 1];
		i++;
	}

	return (1);
}
