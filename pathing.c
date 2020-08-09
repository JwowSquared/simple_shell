#include "header_shell.h"
/**
* fix_path - checks if command exists in any directory in PATH
* @t: pointer to token to fix
* @envc: environment variables array
*
* Return: 1 on success, 0 on fail
*/
int fix_path(token *t, char **envc)
{
	struct stat st;
	token *path_token;
	int i = 0, match_found = 0, status = 0;
	char *path;

	while (t->arguments[0][i])
		if (t->arguments[0][i++] == '/')
			return (1);
	i = 0;
	path = getenv_value("PATH", envc);
	if (path == NULL)
		return (0);
	path_token = create_token(path, ':', '\0', NULL);
	if (path_token == NULL)
		return (0);
	while (path_token->arguments[i] != NULL)
	{
		path = _strcat(path_token->arguments[i], t->arguments[0], '/');
		if (!stat(path, &st))
		{
			match_found = 1;
			break;
		}
		free(path);
		i++;
	}
	if (match_found)
	{
		free(t->arguments[0]);
		t->arguments[0] = path;
		status = 1;
	}
	free_token(path_token);
	return (status);
}
/*For the Glory of PLASTIC CHILDRENS PRODUCTS*/
