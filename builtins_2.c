#include "header_shell.h"

/**
 *
 */
int cd_shell(token *t, char **buffer, char ***envc)
{
	int oldpwd, curpwd;
	char *newwork = malloc(sizeof(char) * 32);
	char *oldwork = malloc(sizeof(char) * 32);

	(void)buffer;

	curpwd = findenvi("PWD", *envc);
	oldpwd = findenvi("OLDPWD", *envc);
	getcwd(oldwork, 32);
	if(!t->arguments[1])
	{
		change_env(oldpwd, _getenv("PWD", *envc), 4, envc);
		change_env(curpwd, _getenv("HOME", *envc), 5, envc);
		chdir(_getenv("HOME", *envc) + 5);
		return (1);
	}
	if (t->arguments[1][0] == '-')
	{
		change_env(curpwd, _getenv("OLDPWD", *envc), 7, envc);
		chdir(_getenv("OLDPWD", *envc) + 7);
		change_env(oldpwd, oldwork, 0, envc);
		free(oldwork);
		return (1);
	}
	if(chdir(t->arguments[1]))
	{
		perror("failed to change directory");
		return (1);
	}
	getcwd(newwork, 32);
	change_env(curpwd, newwork, 0, envc);
 	change_env(oldpwd, oldwork, 0, envc);
	free(oldwork);
	free(newwork);
	return (1);
}

void change_env(int i, char *order, int inc, char ***envc)
{
	int j = 0;
	char *temp = malloc(sizeof(char) * 32);

	while((*envc)[i][j] != '=')
	{
		temp[j] = (*envc)[i][j];
		j++;
	}
	temp[j] = 0;
	order += inc;
	free((*envc)[i]);
	(*envc)[i] = _strcat(temp, order, '=');
	free(temp);
}
