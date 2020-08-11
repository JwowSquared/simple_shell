#include "header_shell.h"

/**
*
*/
int exit_shell(token **cmds, int idx, db_t *db)
{
	int i = -1, illegal = 0, status = db->stat;
	token *t = cmds[idx];

	if (t->args[1] != NULL)
	{
		while (t->args[1][++i])
			if (t->args[1][i] < '0' || t->args[1][i] > '9')
			{
				illegal = 1;
				break;
			}

		if (illegal)
		{
			status = 2;
			print_error(db, t, "Illegal number: ", 1);
		}
		else
			status = _atoi(t->args[1]);
	}
	free_tokens(cmds);
	free_database(db);
	exit(status);

	return (1);
}

int setenv_shell(token **cmds, int idx, db_t *db)
{
	int i;
	token *t = cmds[idx];
	char **temp, *pair;

	if (t->args[1] == NULL || t->args[2] == NULL)
		return (1);

	i = find_env(t->args[1], db);
	if (i == -1)
	{
		pair = _strcat(t->args[1], "=", t->args[2]);
		temp = copy_aos(db->envc, pair);
		free(pair);
		free_aos(&db->envc);
		db->envc = temp;
	}
	else
		update_env(t->args[1], t->args[2], db);

	return (1);
}

int env_shell(token **cmds, int idx, db_t *db)
{
	int i = 0;

	(void)cmds;
	(void)idx;

	while (db->envc[i] != NULL)
	{
		_puts(db->envc[i++], 1);
		_puts("\n", 1);
	}

	return (1);
}

int unsetenv_shell(token **cmds, int idx, db_t *db)
{
	int i;
	token *t = cmds[idx];

	if (t->args[1] == NULL)
		return (1);

	i = find_env(t->args[1], db);
	if (i == -1)
		return (1);

	free(db->envc[i]);
	db->envc[i] = db->envc[i + 1];
	i++;

	while (db->envc[i] != NULL)
	{
		db->envc[i] = db->envc[i + 1];
		i++;
	}

	return (1);
}

int cd_shell(token **cmds, int idx, db_t *db)
{
	char *destination = NULL;
	token *t = cmds[idx];

	if (t->args[1] == NULL)
		destination = getenv_value("HOME", db);
	else if (!_strcmp(t->args[1], "-"))
		destination = getenv_value("OLDPWD", db);
	else
		destination = t->args[1];

	if (destination == NULL || !_strcmp(destination, getenv_value("PWD", db)))
	{
		if (!_strcmp(t->args[1], "-"))
		{
			getcwd(*db->buf, 1024);
			_puts(*db->buf, 1);
			_puts("\n", 1);
		}
		return (1);
	}

	if (!chdir(destination))
	{
		getcwd(*db->buf, 1024);
		update_env("OLDPWD", getenv_value("PWD", db), db);
		update_env("PWD", *db->buf, db);
		if (!_strcmp(t->args[1], "-"))
		{
			_puts(*db->buf, 1);
			_puts("\n", 1);
		}
	}
	else
		print_error(db, t, "can't cd to ", 1);

	return (1);
}
