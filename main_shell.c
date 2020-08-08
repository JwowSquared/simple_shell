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
	token *t;
	char *buffer, **envc;
	size_t buffer_size = 1024;

	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	/* malloc buffer and copy environment variables into envc */
	if (!setup_buffers(&buffer, buffer_size, &envc, &envp))
		exit(-1);
	/* loop forever */
	while (1)
	{
		/* get commandline input, break on EoF */
		_putchar('$');
		if (getline(&buffer, &buffer_size, stdin) == -1)
			break;
		/* break input line into an array of strings */
		t = create_token(&buffer, ' ', '\n');
		if (t == NULL)
			break;
		fix_path(t, envc);
		/* avoid fork if token is a builtin command */
		if (!check_builtin(t, &buffer, &envc))
		{
			/* fork and have child execute command */
			if (!fork())
			{
				execve(t->arguments[0], t->arguments, envc);
				perror(NULL);
				exit(2);
			}
			wait(NULL);
		}
		free_token(t);
	}
	free(buffer);
	free_aos(&envc, 0);
	return (0);
}

/**
* check_builtin - checks if the command to run is a builtin
* @t: token with command and arguments
* @buffer: char array to free on exit
* @envc: pointer to environment variables
*
* Return: 1 if token is builtin, else 0
*/
int check_builtin(token *t, char **buffer, char ***envc)
{
	int i = 0;
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
			return (builtins[i].f(t, buffer, envc));
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
/**
* print_token - this is for debugging and will be deleted eventually
* @t: token
*/
void print_token(token *t)
{
	int i = 0;

	printf("t->argc=%d\n", t->argc);
	while (i < t->argc)
	{
		printf("t->arguments[%d]=%s\n", i, t->arguments[i]);
		i++;
	}
}
