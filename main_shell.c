#include "header_shell.h"

/**
* main - main function for simple_shell
* @ac: unused, needed for envp
* @av: unsued, needed for envp
* @envp: array of environment variables for execve command
*
* Return: -1 on malloc fail, else 0. Child returns 2 on execve fail
*/
int main(int ac, char **av, char **envp)
{
	token **tokens;
	char *buffer, **envc;
	size_t buffer_size = 1024, i = 0, line_number = 1;
	int status = 0;

	(void)ac;
	signal(SIGINT, SIG_IGN);
	if (!setup_buffers(&buffer, buffer_size, &envc, &envp))
		exit(-1);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_string("$ ");
		if (getline(&buffer, &buffer_size, stdin) == -1)
			break;
		tokens = create_tokens(buffer);
		if (tokens == NULL)
			break;
		for (i = 0; tokens[i] != NULL; i++)
		{
			if (!check_builtin(tokens, i, &buffer, &envc))
			{
				if (fix_path(tokens[i], envc))
				{
					if (!fork())
					{
						execve(tokens[i]->arguments[0], tokens[i]->arguments, envc);
						perror(NULL);
						exit(2);
					}
					wait(&status);
				}
				else
					print_error(av[0], line_number, tokens[i]->arguments[0]);
			}
		}
		line_number++;
		free_tokens(tokens);
	}
	free(buffer);
	free_aos(&envc, 0);
	return (WEXITSTATUS(status));
}

/**
* check_builtin - checks if the command to run is a builtin
* @ts: array of tokens
* @tid: id of token currently being executed
* @buffer: char array to free on exit
* @envc: pointer to environment variables
*
* Return: 1 if token is builtin, else 0
*/
int check_builtin(token **ts, int tid, char **buffer, char ***envc)
{
	int i = 0;
	token *t = ts[tid];
	builtin_t builtins[] = {
	{"exit", &exit_shell},
	{"env", &env_shell},
	{"setenv", &setenv_shell},
	{"unsetenv", &unsetenv_shell},
	{"cd", &cd_shell},
	{NULL, NULL}
	};

	/* loop through builtins */
	while (builtins[i].key != NULL)
	{
		/* compare token to key of builtins, and run command function if match */
		if (!_strcmp(builtins[i].key, t->arguments[0]))
			return (builtins[i].f(ts, tid, buffer, envc));
		i++;
	}

	return (0);
}

/**
* setup_buffers - malloc's buffer and envc
* @buffer: buffer to malloc
* @s: size of buffer
* @envc: environment variable to copy_aos into
* @envp: given environment variables from the compiler
*
* Return: 1 on success, 0 on malloc failure
*/
int setup_buffers(char **buffer, size_t s, char ***envc, char ***envp)
{
	*buffer = malloc(sizeof(char) * s);
	if (*buffer == NULL)
		return (0);

	*envc = copy_aos(envp, NULL);
	if (*envc == NULL)
	{
		free(*buffer);
		return (0);
	}

	return (1);
}

/*The main line of defense is asprin and beanie babies*/
