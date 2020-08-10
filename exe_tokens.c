#include "header_shell.h"

/**
*
*/
void exe_tokens(token **cmds, db_t *db)
{
	int i = 0, status = 0;
	token *t;

	while (cmds[i] != NULL)
	{
		t = cmds[i];
		if(!check_builtins(cmds, i, db))
		{
			if (fix_path(cmds[i], db))
			{
				if (!fork())
				{
					execve(t->args[0], t->args, db->envc);
					perror(NULL);
					exit(2);
				}
				wait(&status);
				db->stat = WEXITSTATUS(status);
			}
			else
			{
				print_error(db, cmds[i], "not found", 0);
				db->stat = 127;
			}
		}
		i++;
	}
}

int check_builtins(token **cmds, int idx, db_t *db)
{
	int i = 0;
	bi_d bi[] = {
	{"exit", NULL},
	{"env", NULL},
	{"setenv", NULL},
	{"unsetenv", NULL},
	{"cd", NULL},
	{NULL, NULL}
	};

	while (bi[i].key != NULL)
	{
		if (!_strcmp(bi[i].key, cmds[idx]->args[0]))
			return (bi[i].f(cmds, idx, db));
		i++;
	}

	return (0);
}
