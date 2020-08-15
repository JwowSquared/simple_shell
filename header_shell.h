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

/**
* struct builtin_dictionary - [FIXME]
*/
typedef struct builtin_dictionary
{
	char *key;
	int (*f)(token *t, char **buffer, char ***envc);
} builtin_t;

/* Main Shell Prototypes */
token *create_token(char **buffer, const char delim, const char eol);
int count_arguments(char **buffer, const char delim, const char eol);
void free_token(token *t);
void fix_path(token *t, char **envp);
int check_builtin(token *t, char **buffer, char ***envc);
char **copy_aos(char ***input, char *add);
void free_aos(char ***input, int height);
int setup_buffers(char **buffer, size_t s, char ***envc, char ***envp);

/* Builtins */
int exit_shell(token *t, char **buffer, char ***envc);
int env_shell(token *t, char **buffer, char ***envc);
int setenv_shell(token *t, char **buffer, char ***envc);
char *_getenv(const char *name, char **envc);
int findenvi(const char *name, char **envc);

/* Non-Project Prototypes */
char *_strcat(char *dest, char *src, char sep);
int _strcmp(char *s1, char *s2);
int _atoi(char *str);
int _putchar(char c);
void print_string(char *str);

/* Delete Me */
void print_token(token *t);

#endif /* SIMPLE_SHELL */
