#include "header_shell.h"

/**
* cd_shell - changes PWD and OLDPWD, and switches into new PWD
* @ts: array of tokens
* @tid: id of token currently being executed
* @buffer: buffer where we store the result of getcwd
* @envc: environment variables
* @name: not needed in this function
*
* Return: always 1
*/
int cd_shell(token **ts, int tid, char **buffer, char ***envc, char *name)
{
	char *destination = NULL, *cmd, *arg;
	token *t = ts[tid];

	(void)name;
	if (t->arguments[1] == NULL)
		/* attempt to switch into HOME's value */
		destination = getenv_value("HOME", *envc);
	else if (!_strcmp(t->arguments[1], "-"))
	{
		destination = getenv_value("OLDPWD", *envc);
		if (destination == NULL)
		{
			getcwd(*buffer, 1024);
			print_string(*buffer, 1);
			_putchar('\n', 1);
		}
	}
	else
		/* attempt to switch into given value */
		destination = t->arguments[1];

	/* If destination is equal to PWD, dont do anything */
	if (!_strcmp(destination, getenv_value("PWD", *envc)))
		return (1);

	if (destination == NULL)
		return (1);

	if (!chdir(destination))
	{
		getcwd(*buffer, 1024);
		update_env("OLDPWD", getenv_value("PWD", *envc), envc);
		update_env("PWD", *buffer, envc);
		if (!_strcmp(t->arguments[1], "-"))
		{
			print_string(*buffer, 1);
			_putchar('\n', 1);
		}
	}
	else
	{
		cmd = t->arguments[0];
		arg = t->arguments[1];
		print_error(name, t->ln, cmd, "can't cd to ", arg);
	}
	return (1);
}

/**
* getenv_value - finds env matching with key and returns pointer to value
* @key: key to match with
* @envc: environment variables
*
* Return: pointer to match in envc array, but after the equals sign
*/
char *getenv_value(char *key, char **envc)
{
	int len = 1, i;

	while (key[len - 1])
		len++;

	i = findenvi(key, envc);

	/* Return NULL if key doesnt exist for some reason */
	if (i == -1)
		return (NULL);
	if (*(envc[i] + len) == '\0')
		return (NULL);
	return (envc[i] + len);
}

/**
* update_env - updates env that matches key with value
* @key: key to match with
* @value: value to overwrite with
* @envc: environment variables
*
* Return: 0 on failure, else 1
*/
int update_env(char *key, char *value, char ***envc)
{
	int i = findenvi(key, *envc);
	/* dont do anything if env or value doesnt exist */
	if (key == NULL || value == NULL)
		return (0);
	if (i == -1)
		*envc = copy_aos(envc, _strcat(key, value, '='));
	else
	{
		free((*envc)[i]);
		(*envc)[i] = _strcat(key, value, '=');
	}
	return (1);
}

/*The Glory of Life is Skyrim*/
