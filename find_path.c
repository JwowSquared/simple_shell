#include "header_shell.h"

/**
*
*/
int find_path(char **t, char **envp)
{
	int i = 0, j = 0, match_found = 0, status = 0;
	struct stat st;
	char **path_tokens, *path = getenv_value("PATH", envp);

	while (t[0][j])
		if(t[0][j++] == '/')
			return (1);

	path_tokens = create_tokens(path, ':');
	if (path_tokens == NULL)
		return (0);

	while (path_tokens[i] != NULL)
	{
		path = _strcat(path_tokens[i], "/", t[0]);
		if (!stat(path, &st))
		{
			match_found = 1;
			break;
		}
		free(path);
		i++;
	}
	if (match_found)
	{
		free(t[0]);
		t[0] = path;
		status = 1;
	}
	free_tokens(&path_tokens);
	return (status);
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

	for (i = 0; left[i]; i++)
		out[i] = left[i];

	if (delim != NULL)
		out[i++] = delim[0];

	for (len = 0; right[len]; len++)
		out[i + len] = right[len];

	out[i + len] = '\0';

	return (out);
}

char *getenv_value(char *key, char **envp)
{
	int len = 0, i = find_env(key, envp);

	if (i == -1)
		return (NULL);

	while (key[len])
		len++;

	return (envp[i] + len + 1);
}

/**
*
*/
int find_env(char *key, char **envp)
{
	int i = 0, j = 0;

	while (envp[i] != NULL)
	{
		for (j = 0; key[j] != '\0'; j++)
		{
			if (key[j] != envp[i][j])
				break;
		}
		if (envp[i][j] == '=')
			return (i);
		i++;
	}

	return (-1);
}
