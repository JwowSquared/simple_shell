#include "header_shell.h"
/**
* fix_path - checks if command exists in any directory in PATH
* @t: pointer to token to fix
* @envc: environment variables array
*/
void fix_path(token *t, char **envc)
{
	DIR *d;
	struct dirent *dir;
	token *path_token;
	int i = 0, match_found = 0;
	char *temp, *path;

	/* grab path value, create path token */
	path = getenv_value("PATH", envc);
	if (path == NULL)
		return;
	path_token = create_token(path, ':', '\0', NULL);
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
	}

	free_token(path_token);
}
