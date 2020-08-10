#include "header_shell.h"
/**
 * print_string - prints an input string using _putchar
 * @str: string to print
 * @fd: stdout or stderr
 */
void print_string(char *str, int fd)
{
	int i = 0;

	if (str == NULL)
		return;

	while (str[i])
		_putchar(str[i++], fd);
}

/**
* print_error - prints a detailed error when a command fails
* @s1: program name
* @i: number of lines
* @s2: command that failed
* @s3: command specific prompt
* @s4: optional extra info
*/
void print_error(char *s1, int i, char *s2, char *s3, char *s4)
{
	print_string(s1, 2);
	print_string(": ", 2);
	int_recursion(i);
	print_string(": ", 2);
	print_string(s2, 2);
	print_string(": ", 2);
	print_string(s3, 2);
	if (s4 != NULL)
		print_string(s4, 2);
	print_string("\n", 2);
}
/**
* int_recursion - prints an integer recursively
* @i: integer to print
*/
void int_recursion(int i)
{
	int digit;

	if (i == 0)
		return;
	digit = i % 10;
	int_recursion(i / 10);
	_putchar(digit + 48, 2);
}
