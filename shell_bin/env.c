#include "header_builtins.h"
/**
 * main - [FIXME]
 */
int main(int argc, char *argv[], char **envp)
{
	int i;

	(void)argc;
	(void)argv;

	for (i = 0; envp[i]; i++)
	{
		print_string(envp[i]);
		_putchar('\n');
	}
	return (0);
}

/**
* print_string - [FIXME]
*/
void print_string(char *str)
{
	int i = 0;

	while (str[i])
		_putchar(str[i++]);
}
