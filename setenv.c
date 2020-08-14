#include "header_shell.h"
/**
 *
 */
void _setenv(token *t, char **envc)
{
	int i = findenvi(t->arguments[1], envc), len, j;

	if(t->argc != 3)
	{
		perror("Usage: setenv [VARIABLE] [VALUE]");
		return;
	}
	if (envc[i] == NULL)
		envc = copy_aos(envc, _strcat(t->arguments[1], t->arguments[2], '='));
	else
	{
		free(envc[i]);
		envc[i] = _strcat(t->arguments[1], t->arguments[2], '=');
		printf("goit throguh else");
	}
}

/**
 * _getenv - get an environment variable from the master list
 * @name: the name of the ev that you are searching for
 * @envp: ev master list
 * Return: pointer to string of requested ev
 */
int findenvi(const char *name, char **envc)
{
        int i = 0, j = 0;

        while (envc[i])
        {
                while (name[j])
                {
                        if (name[j] != envc[i][j])
                                break;
                        j++;
                }
                if (name[j] == '\0')
                        return (i);
                i++;
        }
        return (i);
}
