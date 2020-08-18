#include "header_shell.h"

/**
* cd_shell - changes PWD and OLDPWD, and switches into new PWD
* @t: string token of arguments
* @buffer: buffer where we store the result of getcwd
* @envc: environment variables
*
* Return: always 1
*/
int cd_shell(token *t, char **buffer, char ***envc)
{
	char *destination = NULL;

	if (t->arguments[1] == NULL)
		/* attempt to switch into HOME's value */
		destination = getenv_value("HOME", *envc);
	else if (!_strcmp(t->arguments[1], "-"))
		/* attempt to switch into OLDPWD's value */
		destination = getenv_value("OLDPWD", *envc);
	else
		/* attempt to switch into given value */
		destination = t->arguments[1];

	/* If destination is equal to PWD, dont do anything */
	if (!_strcmp(destination, getenv_value("PWD", *envc)))
		return (1);

	if (destination != NULL && !chdir(destination))
	{
		getcwd(*buffer, 1024);
		update_env("OLDPWD", getenv_value("PWD", *envc), envc);
		update_env("PWD", *buffer, envc);
	}
	else
		perror(NULL);

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
	if (i == -1 || value == NULL)
		return (0);

	free((*envc)[i]);
	(*envc)[i] = _strcat(key, value, '=');
	return (1);
}

