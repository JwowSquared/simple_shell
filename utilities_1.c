#include "header_shell.h"

/**
*
*/
int _atoi(char *str)
{
	int i, total = 0;

	if (str == NULL)
		return (0);

	for (i = 0; str[i]; i++)
	{
		total *= 10;
		total += (str[i] - 48);
	}

	return (total);
}
