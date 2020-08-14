#include "header_shell.h"
/**
 * fix_path - checks if arguments[0] contains a path, else it prepends "/bin/"
 * @t: pointer to token to fix
 */
void fix_path(token *t, char **envp)
{
	DIR *d;
	struct dirent *dir;
	token *path_token;
	int i = 0, match_found = 0;
	char *temp, *path;

	/* [FIXME] Does this check matter? is this how custom paths work? */
	while (t->arguments[0][i])
		if (t->arguments[0][i++] == '/')
			return;
	/* create path token */
	path = _getenv("PATH", envp) + 5;
	path_token = create_token(&path, ':', '\0');
	/* loop through all paths in the path token */
	for (i = 0; path_token->arguments[i]; i++)
	{
		d = opendir(path_token->arguments[i]);
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
				if (!_strcmp(t->arguments[0], dir->d_name))
				{
					match_found = 1;
					break;
				}
			closedir(d);
		}
		if (match_found)
			break;
	}
	/* concats path to command */
	if (match_found)
		temp = _strcat(path_token->arguments[i], t->arguments[0]);
	else
		temp = _strcat("./shell_bin", t->arguments[0]);
	/* memory cleanup */
	free_token(path_token);
	free(t->arguments[0]);
	t->arguments[0] = temp;
}

/**
 * _getenv - [FIXME]
 */
char *_getenv(const char *name, char **envp)
{
	int i = 0, j = 0;

	while (envp[i])
	{
		while (name[j])
		{
			if (name[j] != envp[i][j])
				break;
			j++;
		}
		if (name[j] == '\0')
			return (envp[i]);
		i++;
	}
	return (NULL);
}
