#include "header_shell.h"

/**
* create_tokens - creates an array of tokens
* @buffer: command line input
*
* Return: pointer to new array of tokens, else NULL
*/
token **create_tokens(char *buffer)
{
	token **out;
	int i = 0, b = 0, argc = 1;

	while (buffer[i])
	{
		if (buffer[i] == ';')
		{
			argc++;
			if (i > 0 && buffer[i - 1] == ';')
				return (NULL);
		}
		i++;
	}

	out = malloc(sizeof(token *) * (argc + 1));
	if (out == NULL)
		return (NULL);

	for (i = 0; i < argc - 1; i++)
		out[i] = create_token(buffer, ' ', ';', &b);
	out[i++] = create_token(buffer, ' ', '\n', &b);
	out[i] = NULL;
	return (out);
}

/**
 * create_token - create a command token for execution
 * @buffer: buffer of command and arguments passed to create_token
 * @delim: delimiter charactder for parsing of input buffer
 * @eol: end of line character
 * @b: integer pointer to increment buffer past, if applicable
 *
 * Return: pointer to token struct after parsing of original buffer
 */
token *create_token(char *buffer, const char delim, const char eol, int *b)
{
	int len = 0, i = 0, j = 0, argi = 0;
	token *out;

	if (b != NULL)
		buffer += *b;
	len = count_arguments(buffer, delim, eol, b);
	if (len == 0)
		return (NULL);
	out = malloc(sizeof(token));
	if (out == NULL)
		return (NULL);
	out->argc = len;
	out->arguments = malloc(sizeof(char *) * (out->argc + 1));
	if (out->arguments == NULL)
		return (NULL);
	while (argi < out->argc)
	{
		len = 0;
		while (buffer[i] == delim)
			i++;
		/* get length of current argument */
		while (buffer[i + len] != eol && buffer[i + len] != delim)
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
			out->arguments[argi][j] = buffer[i + j];
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
 * @b: integer pointer to increment buffer forward past previous commands
 *
 * Return: number (int) of arguments determined from buffer
 */
int count_arguments(char *buffer, const char delim, const char eol, int *b)
{
	int out = 0, i = 0;

	if (buffer[i] != delim && buffer[i] != eol)
		out++;

	while (buffer[i] != eol)
	{
		if (buffer[i] == delim)
		{
			while (buffer[i] == delim)
				i++;
			if (out == 0 && buffer[i] == eol)
				break;
			out++;
		}
		else
			i++;
	}
	if (b != NULL)
		*b += i + 1;

	return (out);
}

/**
* free_tokens - frees an array of tokens
* @t: array of tokens to free
*/
void free_tokens(token **t)
{
	int i = 0, j = 0;

	while (t[i] != NULL)
		i++;
	while (j < i)
		free_token(t[j++]);

	free(t);
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
