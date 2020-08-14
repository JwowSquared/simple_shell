#include "header_shell.h"
/**
 * main - [FIXME]
 */
void _env(char **envc)
{
	int i;

	for (i = 0; envc[i]; i++)
	{
		print_string(envc[i]);
		_putchar('\n');
	}
}
