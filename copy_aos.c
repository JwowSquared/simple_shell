#include "header_shell.h"
/**
* copy_aos - copies an array of strings into new memory potentially
*            freeing input or adding a new string as well
* @input: input array of strings to copy, maybe free
* @add: string to maybe add to the end of the copy, else ignore
*
* Return: pointer to newly allocated array of strings
*/
char **copy_aos(char ***input, char *add)
{
	int i, j, height = 1, length = 0;
	char **output;

	/* determine height of input double array */
	while ((*input)[height - 1])
		height++;
	/* overwrite NULL pointer at the end of input */
	if (add != NULL)
		(*input)[height++ - 1] = add;
	/* malloc array of char pointers */
	output = malloc(sizeof(char *) * height);
	if (output == NULL)
		return (NULL);
	/* copy each string for each pointer in output */
	for (i = 0; i < height - 1; i++)
	{
		/* find length of string to copy */
		for (length = 0; (*input)[i][length];)
			length++;
		/* malloc memory to copy string into using length */
		output[i] = malloc(sizeof(char) * length);
		if (output[i] == NULL)
		{
			free_aos(&output, height - 1);
			return (NULL);
		}
		/* copy each string into new memory, 1 char at a time */
		for (j = 0; (*input)[i][j]; j++)
			output[i][j] = (*input)[i][j];
		output[i][j] = '\0';
	}
	/* memory cleanup */
	output[i] = NULL;
	if (add != NULL)
		free_aos(input, height - 2);
	return (output);
}

/**
* free_aos - frees an array of strings
* @input: array of strings to free
* @height: known height of array of strings
*/
void free_aos(char ***input, int height)
{
	/* if input height is 0, find the real height */
	if (height == 0)
	{
		while ((*input)[height])
			height++;
	}

	while (height >= 0)
		free((*input)[height--]);
	free(*input);
}
