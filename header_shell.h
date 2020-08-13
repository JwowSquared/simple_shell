#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

/* Structs */
/**
 * struct command_token - parsed command line for relevant data stored for use
 * @arguments: array of arguments, starting with the command
 * @argc: argument count
 */
typedef struct command_token
{
	char **arguments;
	int argc;
} token;

/* Project Prototypes */
token *create_token(char **buffer);
int count_arguments(char **buffer);
void free_token(token *t);
void fix_path(token *t);

/* Non-Project Prototypes */
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);

#endif /* SIMPLE_SHELL */
