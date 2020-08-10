#include "header_shell.h"

/**
*
*/
int fix_path(token *t, db_t *db)
{
	int i = 0, j = 0, match = 0;
	struct stat st;
	char *path = getenv_value("PATH", db);

	while (t->args[0][j])
		if (t->args[0][j++] == '/')
			return (1);

	if (db->paths == NULL)
		db->paths = create_token(path, ':');
	if (db->paths == NULL)
		return (0);

	while (db->paths->args[i] != NULL)
	{
		path = _strcat(db->paths->args[i], "/", t->args[0]);
		if (!stat(path, &st))
		{
			match = 1;
			break;
		}
		free(path);
		i++;
	}

	if (match)
	{
		free(t->args[0]);
		t->args[0] = path;
	}

	return (match);

}

char *_strcat(char *left, char *delim, char *right)
{
	char *out;
	int len = 0, i = 0;

	while (left[len])
		len++;

	if (delim != NULL)
		len++;

	while (right[i])
		i++;
	len += i;

	out = malloc(sizeof(char) * (len + 1));
	if (out == NULL)
		return (NULL);

	for (i = 0; left[i]; i++)
		out[i] = left[i];

	if (delim != NULL)
		out[i++] = delim[0];

	for (len = 0; right[len]; len++)
		out[i + len] = right[len];

	out[i + len] = '\0';

	return (out);

}
