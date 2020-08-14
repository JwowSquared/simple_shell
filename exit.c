#include "header_shell.h"
/**
 *
 */
void exit_shell(token *t, char **buffer)
{
	int status = _atoi(t->arguments[1]);

	free(*buffer);
	free_token(t);
	exit(status);
}
