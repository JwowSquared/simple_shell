#include "header_shell.h"

/**
* /bin/ls -la
*/
char **create_tokens(char *buffer, char delim)
{
	char **out;
	int len = 0, i = 0, j = 0, k = 0, argc;

	if (buffer == NULL)
		return (NULL);

	while (buffer[len])
		if (buffer[len++] == '\n')
			buffer[len - 1] = '\0';

	argc = count_args(buffer, delim);

	out = malloc(sizeof(char *) * (argc + 1));
	/* Malloc fail? */

	while (k < argc)
	{
		len = 0;
		while (buffer[i] == delim)
			i++;

		while (buffer[i + len] != delim && buffer[i + len])
			len++;

		out[k] = malloc(sizeof(char) * (len + 1));
		/* Malloc fail? */

		for (j = 0; j < len; j++)
			out[k][j] = buffer[i + j];
		out[k++][j] = '\0';
		i = i + j;
	}

	out[k] = NULL;
	return (out);
}

void free_tokens(char ***t)
{
	int i = 0;

	while ((*t)[i] != NULL)
		free((*t)[i++]);
	free(*t);
}

int count_args(char *buffer, char delim)
{
	char eol = '\0';
	int out = 1, i = 0;

	while (buffer[i] == delim)
		i++;

	if (buffer[i] == eol)
		return (0);

	while (buffer[i] != eol)
	{
		if (buffer[i] == delim)
		{
			while (buffer[i] == delim)
				i++;
			if (buffer[i] == eol)
				break;
			out++;
		}
		else
			i++;
	}

	return (out);
}
