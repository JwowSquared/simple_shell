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
        int i = 0, ifbuiltin = 0;
        char *temp, *path;

        while (t->arguments[0][i])
        {
                if (t->arguments[0][i++] == '/')
                        return;
        }
	path = _getenv("PATH", envp);
	path += 5;
	path_token = create_token(&path, ':', '\0');
	for (i = 0; path_token->arguments[i]; i++)
	{
		d = opendir(path_token->arguments[i]);
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				if(!_strcmp(t->arguments[0], dir->d_name))
				{
					ifbuiltin = 1;
					break;
				}
			}
			closedir(d);
		}
		if (ifbuiltin == 1)
			break;
	}
        if (ifbuiltin == 0)
                temp = _strcat("./shell_bin", t->arguments[0]);
        else
	{
                temp = _strcat(path_token->arguments[i], t->arguments[0]);
	}
	free_token(path_token);
	free(t->arguments[0]);
	t->arguments[0] = temp;
}

/**
 *
 */
char *_getenv(const char *name,char **envp)
{
	int i = 0, j = 0;

	while(envp[i])
	{
		while(name[j])
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
