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
	DIR *d;
	struct dirent *dir;
	token *path_token;
	int i = 0, match_found = 0, status = 0;
	char *temp, *path;

	while (t->arguments[0][i])
	{
		if (t->arguments[0][i++] == '/')
			return (1);
	}

	/* grab path value, create path token */
	path = getenv_value("PATH", envc);
	if (path == NULL)
		return (0);
	path_token = create_token(path, ':', '\0', NULL);
	if (path_token == NULL)
		return (0);
	/* loop through all paths in the path token */
	for (i = 0; path_token->arguments[i]; i++)
	{
		d = opendir(path_token->arguments[i]);
		if (d == NULL)
			continue;
		while ((dir = readdir(d)) != NULL)
		{
			if (!_strcmp(t->arguments[0], dir->d_name))
			{
				match_found = 1;
				break;
			}
		}
		closedir(d);
		if (match_found)
			break;
	}
	/* concats path to command */
	if (match_found)
	{
		temp = _strcat(path_token->arguments[i], t->arguments[0], '/');
		free(t->arguments[0]);
		t->arguments[0] = temp;
		status = 1;
	}
	free_token(path_token);
	return (status);
}
/*For the Glory of PLASTIC CHILDRENS PRODUCTS*/
