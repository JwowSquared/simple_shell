#include "header_shell.h"

/**
* _strcmp - compares two strings ASCII values and returns result
* @s1: pointer to input string 1
* @s2: pointer to input string 2
*
* Return: numerical difference of most recent dissimilar character, else zero
*/
int _strcmp(char *s1, char *s2)
{
	int result = 0;
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (result == 0 && s1[i] && s2[i])
	{
		result = s1[i] - s2[i];
		i++;
	}

	if (result == 0)
		result = s1[i] - s2[i];

	return (result);
}
