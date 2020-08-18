#include "header_shell.h"
/**
* exit_shell - [FIXME]
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
* _env - [FIXME]
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
* _setenv - [FIXME]
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
	if ((*envc)[i] == NULL)
		*envc = copy_aos(envc, _strcat(t->arguments[1], t->arguments[2], '='));
	else
	{
		free((*envc)[i]);
		(*envc)[i] = _strcat(t->arguments[1], t->arguments[2], '=');
	}

	return (1);
}

/**
* findenvi - [FIXME]
* @name: the name of the ev that you are searching for
* @envp: ev master list
* Return: pointer to string of requested ev
*/
int findenvi(const char *name, char **envc)
{
	int i = 0, j = 0;

	while (envc[i])
	{
		while (name[j])
		{
			if (name[j] != envc[i][j])
				break;
			j++;
		}
		if (name[j] == '\0')
			return (i);
		i++;
	}
	return (i);
}

/**
 *
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
	if ((*envc)[i] == NULL)
	{
		perror("Could not find variable");
		return (1);
	}
	else
	{
		free((*envc)[i]);
		(*envc)[i] = (*envc)[i + 1];
		i++;
		while((*envc)[i])
		{
			(*envc)[i] = (*envc)[i + 1];
			i++;
		}
	}

	return (1);
}
