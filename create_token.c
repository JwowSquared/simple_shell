#include "header_shell.h"

/**
 * create_token - create a command token for execution
 * @buffer: buffer of command and arguments passed to create_token
 * Return: pointer to token struct after parsing of original buffer
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
	out->argc = argc;
	out->arguments = malloc(sizeof(char *) * (argc + 1));
	if (out->arguments == NULL)
		return (NULL);
	/*setting the arguments*/
	while (argc > 0)
	{
		len = 0;
		while ((*buffer)[i] == ' ')
			i++;

		while ((*buffer)[i + len] != '\n' && (*buffer)[i + len] != ' ')
			len++;

		out->arguments[argi] = malloc(sizeof(char) * (len + 1));
		if (out->arguments[argi] == NULL)
			return (NULL);
		j = 0;
		while (j < len)
		{
			out->arguments[argi][j] = (*buffer)[i + j];
			j++;
		}
		out->arguments[argi][j] = '\0';
		i += j;
		argi++;
		argc--;
	}
	/*end setting arguments*/
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
* fix_path - checks if arguments[0] contains a path already, and if not, it prepends "/bin/"
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
