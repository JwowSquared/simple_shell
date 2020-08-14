#include "header_shell.h"
/**
 *
 */
char **copy_aos(char **input, char *add)
{
	int i, j, size = 0, length = 0;
	char **output;

	printf("entered copy_aos\n");
	for(i = 0; input[i]; i++)
		size++;
	size++;
	if(add)
		size++;
	output = malloc(sizeof(char *) * size);
	printf("first malloc done\n");
	for(i = 0; input[i]; i++)
	{
		printf("looping through double array: %d\n", i);
		length = 0;
		for (j = 0; input[i][j]; j++)
			length++;
		output[i] = malloc(sizeof(char) * length);
		for (j = 0; input[i][j]; j++)
			output[i][j] = input[i][j];
		output[i][j] = 0;
/*		if(add != NULL)
			free(input[i]);
*/	}
	if(add)
	{
		length = 0;
		for (j = 0; add[j]; j++)
			length++;
		output[i] = malloc(sizeof(char) * length);
		for (j = 0; add[j]; j++)
			output[i][j] = add[j];
		output[i++][j] = 0;
	}
	output[i] = 0;
/*	if(!add)
 		free(input);
*/	return (output);
}
