#include "header_shell.h"
/**
 * main - main function for simple_shell
 * @ac: number of arguments
 * @av: arguments passed to shell intialization
 * Return: of the Jedi
 */
int main(void)
{
	token *t;
	char *envParms[2] = {"PWD=/home/vagrant/shell/simple_shell", NULL};
	char *buffer, *temp, *default_path = "/bin/";
	size_t buffer_size = 1024;
	int looping = 1, result;

	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		return (1);

	while (looping)
	{
		getline(&buffer, &buffer_size, stdin);
		t = create_token(&buffer);
		if (t == NULL)
			return (1);

		temp = _strcat(default_path, t->command);
		result = execve(temp, t->arguments, envParms);

	}

	return (0);
}
