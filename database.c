#include "header_shell.h"

/**
*
*/
db_t *create_database(char **buf, size_t s, char *exe, char **envp)
{
	db_t *db = malloc(sizeof(db_t));
	if (db == NULL)
		return (NULL);

	db->exe = exe;
	db->buf = buf;
	db->ln = 1;
	db->stat = 0;
	db->paths = NULL;
	*buf = malloc(sizeof(char) * s);
	if (*buf == NULL)
	{
		free(db);
		return (NULL);
	}

	db->envc = copy_aos(envp, NULL);
	if (db->envc == NULL)
	{
		free(*buf);
		free(db);
		return (NULL);
	}

	return (db);
}

/**
*
*/
int free_database(db_t *db)
{
	int status = db->stat;

	free(*db->buf);
	free_aos(&db->envc);
	free_token(db->paths);
	free(db);

	return status;
}

void print_database(db_t *db)
{
	printf("BUFFER=%s", *db->buf);
	printf("ln=%d|stat=%d\n", db->ln, db->stat);
	printf("av[0]=%s|envc[0]=%s\n", db->exe, db->envc[0]);
}
