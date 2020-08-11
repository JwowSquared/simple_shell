#include "header_shell.h"

/**
* DOCUMENTATION
*/
token *create_token(char **buffer)
{

	int len = 0, i = 0, j = 0, argc, argi = 0;
	token *out;

	argc = count_arguments(buffer);
	if (argc == -1)
		return (NULL);

	out = malloc(sizeof(token));
	if (out == NULL)
		return (NULL);

	while ((*buffer)[i + len] != '\n')
	{
		if ((*buffer)[i + len] == ' ')
		{
			if (len == 0)
				i++;
			else
				break;
		}
		else
			len++;
	}

	out->command = malloc(sizeof(char) * len);
	if (out->command == NULL)
		return (NULL);

	while (j < len)
	{
		out->command[j] = (*buffer)[i + j];
		j++;
	}
	i += j;
	out->argc = argc;
	out->arguments = malloc(sizeof(char *) * (argc + 1));
	if (out->arguments == NULL)
		return (NULL);
	while ((*buffer)[i] == ' ')
		i++;

	while (argc > 0)
	{
		len = 0;
		while ((*buffer)[i] == ' ')
			i++;

		while ((*buffer)[i + len] != '\n' && (*buffer)[i + len] != ' ')
			len++;

		out->arguments[argi] = malloc(sizeof(char) * len);
		if (out->arguments[argi] == NULL)
			return (NULL);
		j = 0;
		while (j < len)
		{
			out->arguments[argi][j] = (*buffer)[i + j];
			j++;
		}

		i += j;

		argi++;
		argc--;
	}

	out->arguments[argi] = NULL;
	return (out);
}

/**
* DOCUMENTATION
*/
int count_arguments(char **buffer)
{
	int out = 0, i = 0;

	if ((*buffer)[i] != ' ')
		out++;

	while ((*buffer)[i] != '\n')
	{
		if ((*buffer)[i] == ' ')
		{
			while ((*buffer)[i] == ' ')
				i++;
			if ((*buffer)[i] == '\n')
				break;
			out++;
		}
		i++;
	}

	return (out - 1);
}
