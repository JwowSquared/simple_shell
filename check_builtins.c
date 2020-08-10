#include "header_shell.h"

int check_builtins(char ***t, char **b, char **e)
{
	int i = 0;
	builtin_t builtins[] = {
		{"exit", &exit_shell},
		{"env", &env_shell},
		{NULL, NULL}
	};

	while (builtins[i].key != NULL)
	{
		if (!strcmp((*t)[0], builtins[i].key))
			return (builtins[i].f(t, b, e));
		i++;
	}

	return (0);
}

int exit_shell(char ***t, char **b, char **e)
{
	(void)e;
	free(*b);
	free_tokens(t);
	exit(0);

	return (1);
}

int env_shell(char ***t, char **b, char **e)
{
	int i = 0;

	(void)t;
	(void)b;
	while (e[i] != NULL)
		printf("%s\n", e[i++]);

	return (1);
}
