#include "header_shell.h"

/**
*
*/
int update_env(char *key, char *value, db_t *db)
{
	char **temp, *pair;
	int i = find_env(key, db);

	if (key == NULL || value == NULL)
		return (0);
	if (i == -1)
	{
		pair = _strcat(key, "=", value);
		temp = copy_aos(db->envc, pair);
		free(pair);
		free_aos(&db->envc);
		db->envc = temp;
	}
	else
	{
		free(db->envc[i]);
		db->envc[i] = _strcat(key, "=", value);
	}
	return (1);
}

/**
*
*/
char *getenv_value(char *key, db_t *db)
{
	int len = 0, i = find_env(key, db);

	if (i == -1)
		return (NULL);

	while (key[len])
		len++;

	return (db->envc[i] + len + 1);
}

int find_env(char *key, db_t *db)
{
	int i = 0, j = 0;

	while (db->envc[i] != NULL)
	{
		for (j = 0; key[j] != '\0'; j++)
			if (key[j] != db->envc[i][j])
				break;

		if (db->envc[i][j] == '=')
			return (i);

		i++;
	}

	return (-1);
}
