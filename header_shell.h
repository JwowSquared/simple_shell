#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Structs */
/**
 * struct command_token - parsed command line for relevant data stored for use
 * @command: the initial command passed
 * @arguments: subsequent arguments to the initial command
 * @argc: argument count
 */
typedef struct command_token
{
	char *command;
	char **arguments;
	int argc;
} token;

/* Project Prototypes */
token *create_token(char **buffer);
int count_arguments(char **buffer);

/* Non-Project Prototypes */
char *_strcat(char *dest, char *src);

#endif /* SIMPLE_SHELL */
