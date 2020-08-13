#include "header_shell.h"

/**
 * create_token - create a command token for execution
 * @buffer: buffer of command and arguments passed to create_token
 * Return: pointer to token struct after parsing of original buffer
 */
token *create_token(char **buffer)
{
	int len = 0, i = 0, j = 0, argi = 0;
	token *out;

	/* malloc a new token and initialize arguments */
	out = malloc(sizeof(token));
	if (out == NULL)
		return (NULL);
	out->argc = count_arguments(buffer);
	out->arguments = malloc(sizeof(char *) * (out->argc + 1));
	if (out->arguments == NULL)
		return (NULL);
	/* malloc a new string to go in arguments, out->argc number of times */
	while (argi < out->argc)
	{
		len = 0;
		while ((*buffer)[i] == ' ')
			i++;
		/* get length of current argument */
		while ((*buffer)[i + len] != '\n' && (*buffer)[i + len] != ' ')
			len++;
		/* malloc a new string using it's length */
		out->arguments[argi] = malloc(sizeof(char) * (len + 1));
		if (out->arguments[argi] == NULL)
		{
			free_token(out);
			return (NULL);
		}
		/* fill out new string with chars from buffer */
		for (j = 0; j < len; j++)
			out->arguments[argi][j] = (*buffer)[i + j];
		/* append a null-byte and move i forward */
		out->arguments[argi++][j] = '\0';
		i += j;
	}
	/* last argument is NULL, and first argument is fixed in fix_path */
	out->arguments[argi] = NULL;
	fix_path(out);
	return (out);
}

/**
 * count_arguments - counts the number of arguments from the given buffer
 * @buffer: buffer containing command and arguments passed to count_arguments
 * Return: number (int) of arguments determined from buffer
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

	return (out);
}

/**
* free_token - frees a token
* @t: pointer to token to free
*/
void free_token(token *t)
{
	int i = 0;

	while (i < t->argc)
		free(t->arguments[i++]);
	free(t->arguments);
	free(t);
}

/**
* fix_path - checks if arguments[0] contains a path, else it prepends "/bin/"
* @t: pointer to token to fix
*/
void fix_path(token *t)
{
	int i = 0;
	char *temp;

	while (t->arguments[0][i])
	{
		if (t->arguments[0][i++] == '/')
			return;
	}
	temp = _strcat("/bin/", t->arguments[0]);
	free(t->arguments[0]);
	t->arguments[0] = temp;
}
