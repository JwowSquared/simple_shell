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
	int ifbuiltin = 0;
	/* ignore ^C signal, and malloc buffer to write in */
	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		exit(-1);
	envc = copy_aos(envp, NULL);
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
		/* [FIXME] Band-aid exit fix */
		ifbuiltin = check_builtin(t, &buffer, envc);
		/* fork and have child execute command */
		if (ifbuiltin == 0)
		{
			if (!fork())
			{
				execve(t->arguments[0], t->arguments, envp);
				perror(NULL);
				exit(2);
			}
			wait(NULL);
		}
		free_token(t);
	}
	free(buffer);
	return (0);
}

/**
* check_exit - frees memory and exits with status if command was exit
* @t: token to free
* @buffer: char array to free
*/
int check_builtin(token *t, char **buffer, char **envc)
{
	int status = 0;

	if(!_strcmp("./exit", t->arguments[0]))
		exit_shell(t, buffer);
	else if(!_strcmp("./env", t->arguments[0]))
	{
		_env(envc);
		status = 1;
	}
	else if(!_strcmp("./setenv", t->arguments[0]))
	{
		_setenv(t, envc);
		status = 1;
	}
	return (status);
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
