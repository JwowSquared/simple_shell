#include "header_shell.h"
/**
* print_string - prints an input string using _putchar
* @str: string to print
*/
void print_string(char *str)
{
	int i = 0;

	if (str == NULL)
		return;

	while (str[i])
		_putchar(str[i++]);
}
