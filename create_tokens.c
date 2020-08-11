#include "header_shell.h"

/**
*
*/
token **create_tokens(char *buf)
{
	int i = 0;
	token **out = malloc(sizeof(token *) * 2);

	if (out == NULL)
		return (NULL);

	while (buf[i])
	{
		if (buf[i] == '\n')
			buf[i] = '\0';
		i++;
	}

	out[0] = create_token(buf, ' ');
	out[1] = NULL;
	return (out);
}

token *create_token(char *buf, char delim)
{
	int height = 0, i = 0, j;
	token *out;

	height = count_args(buf, delim);
	if (height == 0)
		return (NULL);

	out = malloc(sizeof(token));
	if (out == NULL)
		return (NULL);
	out->args = malloc(sizeof(char *) * (height + 1));
	if (out->args == NULL)
	{
		free(out);
		return (NULL);
	}

	while (i < height)
	{
		j = 0;
		while (*buf == delim)
			buf++;

		while (buf[j] != delim && buf[j])
			j++;
		buf[j] = '\0';
		out->args[i] = _strdup(buf);
		if (out->args[i] == NULL)
		{
			free_token(out);
			return (NULL);
		}
		buf += j + 1;
		i++;
	}
	out->args[i] = NULL;
	return (out);
}

int count_args(char *buf, char delim)
{
	int out = 1, i = 0;

	if (!(buf != NULL && *buf != '\0'))
		return (0);

	while (buf[i] == delim)
		i++;

	if (!buf[i])
		return (0);

	while (buf[i])
	{
		if (buf[i] == delim || !buf[i])
		{
			while (buf[i] == delim)
				i++;
			if (!buf[i])
				break;
			out++;
		}
		else
			i++;
	}

	return (out);
}

/**
*
*/
void free_tokens(token **t)
{
	int i = 0;

	if (t == NULL)
		return;

	while (t[i] != NULL)
		free_token(t[i++]);
	free(t);
}

void free_token(token *t)
{
	int i = 0;

	if (t == NULL)
		return;

	while (t->args[i] != NULL)
		free(t->args[i++]);
	free(t->args);
	free(t);
}

void print_tokens(token **t)
{
	int i = 0, j = 0;

	while (t[i] != NULL)
	{
		while (t[i]->args[j] != NULL)
			printf("%s\n", t[i]->args[j++]);
		i++;
	}
}
