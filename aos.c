#include "header_shell.h"

/**
*
*/
char **copy_aos(char **input, char *addme)
{
	int i = 0;
	char **out;

	while (input[i])
		i++;

	out = malloc(sizeof(char *) * (i + 1));
	if (out == NULL)
		return (NULL);

	for (i = 0; input[i] != NULL; i++)
	{
		out[i] = _strdup(input[i]);
		if (out[i] == NULL)
			return (free_aos(&out));
	}

	if (addme != NULL)
	{
		out[i] = _strdup(addme);
		if (out[i] == NULL)
			return (free_aos(&out));
		i++;
	}
	out[i] = NULL;

	return (out);
}

/**
*
*/
char *_strdup(char *input)
{
	int i = 0;
	char *out;

	if (input == NULL)
		return (NULL);

	while (input[i])
		i++;

	out = malloc(sizeof(char) * (i + 1));
	if (out == NULL)
		return (NULL);

	for (i = 0; input[i]; i++)
		out[i] = input[i];
	out[i] = '\0';

	return (out);
}

/**
*
*/
char **free_aos(char ***input)
{
	int i = 0;

	while ((*input)[i] != NULL)
		free((*input)[i++]);
	free(*input);

	return (NULL);
}
