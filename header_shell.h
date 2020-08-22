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

typedef struct error_info {
	int stat;
	int ln;
} e_i;

typedef struct builtin_dictionary {
	char *key;
	int (*f)(char ***, char **, char **);
} builtin_t;

char **create_tokens(char *buffer, char delim);
int count_args(char *buffer, char delim);
void print_tokens(char **t);
void free_tokens(char ***t);
int find_path(char **t, char **envp);
char *_strcat(char *left, char *delim, char *right);
char *getenv_value(char *key, char **envp);
int find_env(char *key, char **envp);
void _puts(char *str);
void print_error(char *, int, char *);
void int_recursion(int i);

int check_builtins(char ***, char **, char **);
int exit_shell(char ***, char **, char **);
int env_shell(char ***, char **, char **);

#endif /* SIMPLE_SHELL */
