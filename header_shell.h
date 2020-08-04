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
typedef struct command_token {
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
