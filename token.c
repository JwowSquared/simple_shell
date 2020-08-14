#include "header_shell.h"

/**
 * create_token - create a command token for execution
 * @buffer: buffer of command and arguments passed to create_token
 * @delim: delimiter charactder for parsing of input buffer
 * @eol: end of line character
 * Return: pointer to token struct after parsing of original buffer
 */
token *create_token(char **buffer, const char delim, const char eol)
{
	int len = 0, i = 0, j = 0, argi = 0;
	token *out;

	/* malloc a new token and initialize arguments */
	out = malloc(sizeof(token));
	if (out == NULL)
		return (NULL);
	out->argc = count_arguments(buffer, delim, eol);
	out->arguments = malloc(sizeof(char *) * (out->argc + 1));
	if (out->arguments == NULL)
		return (NULL);
	/* malloc a new string to go in arguments, out->argc number of times */
	while (argi < out->argc)
	{
		len = 0;
		while ((*buffer)[i] == delim)
			i++;
		/* get length of current argument */
		while ((*buffer)[i + len] != eol && (*buffer)[i + len] != delim)
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
	return (out);
}

/**
 * count_arguments - counts the number of arguments from the given buffer
 * @buffer: buffer containing command and arguments passed to count_arguments
 * @delim: delimiter charactder for parsing of input buffer
 * @eol: end of line character
 * Return: number (int) of arguments determined from buffer
 */
int count_arguments(char **buffer, const char delim, const char eol)
{
	int out = 0, i = 0;

	if ((*buffer)[i] != delim)
		out++;

	while ((*buffer)[i] != eol)
	{
		if ((*buffer)[i] == delim)
		{
			while ((*buffer)[i] == delim)
				i++;
			if ((*buffer)[i] == eol)
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
