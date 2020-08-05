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
	int i = 0, j = 0, k;

	/* get length of left string */
	while (left[i])
		i++;
	/* get length of right string */
	while (right[j])
		j++;
	/* malloc new string */
	out = malloc(sizeof(char) * (i + j + 2));
	if (out == NULL)
		return (NULL);
	/* set left chars */
	for (k = 0; k < i; k++)
		out[k] = left[k];
	/* for our purposes, we separate left and right with a forward slash */
	out[i++] = '/';
	/* set right chars */
	for (k = 0; k < j; k++)
		out[i + k] = right[k];
	/* c strings end in a null byte */
	out[i + k] = '\0';
	return (out);
}
