#include "header_shell.h"

void print_error(db_t *db, token *t, char *prompt, int use_av1)
{
	_puts(db->exe, 2);
	_puts(": ", 2);
	int_recursion(db->ln, 2);
	_puts(": ", 2);
	_puts(t->args[0], 2);
	_puts(": ", 2);
	_puts(prompt, 2);
	if (use_av1)
		_puts(t->args[1], 2);
	_puts("\n", 2);
}

/**
*
*/
void _puts(char *str, int fd)
{
	int i = 0;

	if (str == NULL)
		return;

	while (str[i])
		i++;

	write(fd, str, i);
}

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

void int_recursion(int i, int fd)
{
	int digit;

	if (i == 0)
		return;

	digit = (i % 10) + 48;
	int_recursion(i / 10, fd);
	write(fd, &digit, 1);
}
