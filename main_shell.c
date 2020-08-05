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
	char *buffer;
	size_t buffer_size = 1024;

	/* ignore ^C signal, and malloc buffer to write in */
	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		exit(-1);
	/* loop forever */
	while (1)
	{
		printf("$"); /* [FIXME] cant use printf */
		/* get commandline input, break on EoF */
		if (getline(&buffer, &buffer_size, stdin) == -1)
			break;
		/* break input line into an array of strings */
		t = create_token(&buffer);
		if (t == NULL)
			exit(-1);
		/* [FIXME] handle built-ins to avoid fork */
		/* fork and have child execute command */
		if (!fork())
		{
			execve(t->arguments[0], t->arguments, envp);
			perror(NULL);
			exit(2);
		}
		wait(NULL);
		free_token(t);
	}
	free(buffer);
	return (0);
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
