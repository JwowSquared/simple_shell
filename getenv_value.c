#include "header_shell.h"

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
