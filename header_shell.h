#ifndef _HEADER_SHELL_
#define _HEADER_SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

/**
*
*/
typedef struct command_token {
	char **args;
} token;

/**
*
*/
typedef struct database {
	int ln;
	int stat;
	char *exe;
	char **buf;
	char **envc;
	token *paths;
} db_t;

/**
*
*/
typedef struct builtin_dictionary {
	char *key;
	int (*f)(token **, int, db_t *);
} bi_d;

token **create_tokens(char *buf);
token *create_token(char *buf, char delim);
void exe_tokens(token **cmds, db_t *db);
void free_tokens(token **t);
void free_token(token *t);
void print_tokens(token **t);
int count_args(char *buf, char delim);
int fix_path(token *t, db_t *db);

void print_database(db_t *db);
int free_database(db_t *db);
db_t *create_database(char **, size_t, char *, char **);

char **copy_aos(char **, char *);
char **free_aos(char ***);

void _puts(char *, int);
char *_strdup(char *);
int _strcmp(char *, char *);
char *_strcat(char *left, char *delim, char *right);
void int_recursion(int, int);

int check_builtins(token **, int, db_t *);
char *getenv_value(char *, db_t *);
int find_env(char *, db_t *);

void print_error(db_t *, token *, char *, int);
#endif /* _HEADER_SHELL_ */
