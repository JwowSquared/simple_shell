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

	/*incrementing through leading spaces, recommend a spaces incrementation function*/
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
	/*end incrementing*/

	out->command = malloc(sizeof(char) * len);
	if (out->command == NULL)
		return (NULL);

	/*assigning out->command, maybe not necessary?*/
	while (j < len)
	{
		out->command[j] = (*buffer)[i + j];
		j++;
	}
	i += j; /*<- incrementing i with j probably not necesary, as we want the command to be in out->arguments*/
	out->argc = argc;
	out->arguments = malloc(sizeof(char *) * (argc + 1));
	if (out->arguments == NULL)
		return (NULL);

	/*if we don't increment i with j, then we won't need the while loop*/
	while ((*buffer)[i] == ' ')
		i++;

	/*setting the arguments, reccomend this whole loop be made its own function, something like void set_args(token *, int index)*/
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
	/*end setting arguments*/

	out->arguments[argi] = NULL;
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

	return (out - 1);
}
