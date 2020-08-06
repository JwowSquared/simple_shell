#include "header_shell.h"
/**
* exit_shell - [FIXME]
*/
void exit_shell(token *t, char **buffer, char ***envc)
{
	int status = _atoi(t->arguments[1]);

	free(*buffer);
	free_token(t);
	free_aos(envc);
	exit(status);
}

/**
* _env - [FIXME]
*/
void _env(token *t, char **buffer, char ***envc)
{
	int i;

	(void)t;
	(void)buffer;

	for (i = 0; (*envc)[i]; i++)
	{
		print_string((*envc)[i]);
		_putchar('\n');
	}
}

/**
* _setenv - [FIXME]
*/
void _setenv(token *t, char **buffer, char ***envc)
{
	int i = findenvi(t->arguments[1], *envc);

	(void)buffer;

	if (t->argc != 3)
	{
		perror("Usage: setenv [VARIABLE] [VALUE]");
		return;
	}
	if ((*envc)[i] == NULL)
		*envc = copy_aos(envc, _strcat(t->arguments[1], t->arguments[2], '='));
	else
	{
		free((*envc)[i]);
		(*envc)[i] = _strcat(t->arguments[1], t->arguments[2], '=');
	}
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
