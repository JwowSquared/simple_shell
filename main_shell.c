#include "header_shell.h"
void sighandler(int);
/**
 * main - main function for simple_shell
 * Return: of the Jedi
 */
int main(int ac, char **av, char **envp)
{
	token *t;
	char *buffer;
	size_t buffer_size = 1024;
	int looping = 1, stat;

	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		return (1);
	while (looping)
	{
		printf("$");
		if (getline(&buffer, &buffer_size, stdin) == -1)
		{
			free(buffer);
			exit(-1);
		}
		t = create_token(&buffer);
		if (t == NULL)
			return (1);
/*		if (!_strcmp(t->arguments[0], "exit"))
			exit(-1);
*/		if (fork())
			wait(&stat);
		else
		{
			if (execve(t->arguments[0], t->arguments, envp) == -1)
			{
				perror(NULL);
				exit(-1);
			}
		}
		free_token(t);
	}

	free(buffer);

	return (0);
}

void sighandler(int signum)
{
	printf("CRTL+D? Exit! | Sig=%d\n", signum);
	exit(1);
}
