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
* struct builtin_dictionary - pairs key string with its function to call
* @key: key to match against
* @f: function to call on match
*/
typedef struct builtin_dictionary
{
	char *key;
	int (*f)(token **ts, int tid, char **buffer, char ***envc);
} builtin_t;

/* Main Shell Prototypes */
token *create_token(char *buffer, char delim, char eol, int *b);
token **create_tokens(char *buffer);
int count_arguments(char *buffer, char delim, char eol, int *b);
void free_token(token *t);
void free_tokens(token **t);
int fix_path(token *t, char **envp);
int check_builtin(token **ts, int tid, char **buffer, char ***envc);
char **copy_aos(char ***input, char *add);
void free_aos(char ***input, int height);
int setup_buffers(char **buffer, size_t s, char ***envc, char ***envp);
void print_error(char *s1, int i, char *s2);

/* Builtins */
int exit_shell(token **ts, int tid, char **buffer, char ***envc);
int env_shell(token **ts, int tid, char **buffer, char ***envc);
int setenv_shell(token **ts, int tid, char **buffer, char ***envc);
int unsetenv_shell(token **ts, int tid, char **buffer, char ***envc);
int cd_shell(token **ts, int tid, char **buffer, char ***envc);
int findenvi(char *key, char **envc);
int update_env(char *key, char *value, char ***envc);
char *getenv_value(char *key, char **envc);

/* Non-Project Prototypes */
char *_strcat(char *dest, char *src, char sep);
int _strcmp(char *s1, char *s2);
int _atoi(char *str);
int _putchar(char c, int fd);
void print_string(char *str, int fd);
char *_strdup(char *str);
void int_recursion(int i);

#endif /* SIMPLE_SHELL */
