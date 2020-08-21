#include "header_shell.h"
/**
* exit_shell - cleans up memory and exits program with status
* @ts: array of tokens
* @tid: id of current token being executed
* @buffer: buffer to free
* @envc: environment variables to free
* @name: code to exit with unless specified by token
*
* Return: always 1, but should never return
*/
int exit_shell(token **ts, int tid, char **buffer, char ***envc, char *name)
{
	int i = 0, illegal_number = 0;
	int status = ts[tid]->status, ln = ts[tid]->ln;
	char c, *cmd, *arg;

	if (ts[tid]->arguments[1] != NULL)
	{
		while (ts[tid]->arguments[1][i])
		{
			c = ts[tid]->arguments[1][i++];
			if (!(c >= '0' && c <= '9'))
			{
				illegal_number = 1;
				break;
			}
		}
		if (illegal_number)
		{
			status = 2;
			cmd = ts[tid]->arguments[0];
			arg = ts[tid]->arguments[1];
			print_error(name, ln, cmd, "Illegal number: ", arg);
		}
		else
			status = _atoi(ts[tid]->arguments[1]);
	}

	free(*buffer);
	free_tokens(ts);
	free_aos(envc, 0);
	exit(status);

	return (1);
}

/**
* env_shell - prints environment variables
* @ts: not needed in this function
* @tid: not needed in this function
* @buffer: not needed in this function
* @envc: environment variables to print
* @name: not needed in this function
*
* Return: always 1
*/
int env_shell(token **ts, int tid, char **buffer, char ***envc, char *name)
{
	int i;

	(void)ts;
	(void)tid;
	(void)buffer;
	(void)name;

	for (i = 0; (*envc)[i]; i++)
	{
		print_string((*envc)[i], 1);
		_putchar('\n', 1);
	}

	return (1);
}

/**
* setenv_shell - updates env on match, else create new env
* @ts: array of tokens
* @tid: index of current token being executed
* @buffer: not needed in this function
* @envc: environment variables
* @name: not needed in this function
*
* Return: always 1
*/
int setenv_shell(token **ts, int tid, char **buffer, char ***envc, char *name)
{
	int i;
	token *t = ts[tid];

	(void)buffer;
	(void)name;

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
		if (key[j] == '\0' && envc[i][j] == '=')
			return (i);
		i++;
	}
	/* return -1 if key doesn't exist in envc */
	return (-1);
}

/**
* unsetenv_shell - deletes env in envc
* @ts: array of tokens
* @tid: id of current token being executed
* @b: unused in this function
* @envc: environment variables
* @n: not needed in this function
*
* Return: always 1
*/
int unsetenv_shell(token **ts, int tid, char **b, char ***envc, char *n)
{
	int i;
	token *t = ts[tid];

	(void)b;
	(void)n;

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

/*The water of life is Coca-Cola*/
