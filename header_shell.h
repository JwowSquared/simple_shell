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
#include <dirent.h>

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
token *create_token(char **buffer, const char delim, const char eol);
int count_arguments(char **buffer, const char delim, const char eol);
void free_token(token *t);
void fix_path(token *t, char **envp);
char *_getenv(const char *name, char **envp);
void check_exit(token *t, char **buffer);

/* Non-Project Prototypes */
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _atoi(char *str);
int _putchar(char c);

/* Delete Me */
void print_token(token *t);

#endif /* SIMPLE_SHELL */
