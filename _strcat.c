#include "header_shell.h"

/**
* _strcat - concatenates two strings
* @left: input string 1
* @right: input string 2
*
* Return: pointer to new string, else NULL on malloc failure
*/
char *_strcat(char *left, char *right)
{
	char *out;
	int length, i = 0, j = 0, k = 0;

	while (left[i])
		i++;

	while (right[j])
		j++;
	length = i + j;

	out = malloc(sizeof(char) * length);
	if (out == NULL)
		return (NULL);
	while (k < i)
	{
		out[k] = left[k];
		k++;
	}

	k = 0;
	while (k < j)
	{
		out[i + k] = right[k];
		k++;
	}
		
	return (out);
}
