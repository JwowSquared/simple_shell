#include "header_shell.h"

/**
*
*/
int main(int argc, char **argv, char **envp)
{
	size_t size = 1024;
	char *buffer, **tokens;
	int line_number = 1, status = 0;

	(void)argc;

	buffer = malloc(sizeof(char) * size);
	if (buffer == NULL)
		return (-1);

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		printf("$ ");
		if (getline(&buffer, &size, stdin) == -1)
			break;

		tokens = create_tokens(buffer, ' ');
		if (!check_builtins(&tokens, &buffer, envp))
		{
			if (find_path(tokens, envp))
			{
				if (!fork())
				{
					execve(tokens[0], tokens, envp);
					perror(NULL);
					exit(2);
				}
				else
				{
					wait(&status);
					status = WEXITSTATUS(status);
				}
			}
			else
			{
				print_error(argv[0], line_number, tokens[0]);
				status = 127;
			}
			line_number++;
			free_tokens(&tokens);
		}
	}

	free(buffer);

	exit(status);
}

void print_error(char *exe, int i, char *cmd)
{
	_puts(exe);
	_puts(": ");
	int_recursion(i);
	_puts(": ");
	_puts(cmd);
	_puts(": not found\n");
}

void int_recursion(int i)
{
	char digit;

	if (i == 0)
		return;
	digit = (i % 10) + 48;
	int_recursion(i / 10);
	write(2, &digit, 1);
}

void _puts(char *str)
{
        unsigned int length;
        length = strlen(str);
        write(2, str, length);
}

void print_tokens(char **t)
{
	int i = 0;

	while (t[i] != NULL)
		printf("%s\n", t[i++]);
}
