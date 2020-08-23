#include "header_shell.h"

/**
*
*/
int main(int ac, char **av, char **envp)
{
	/* Setup: Buffer, ec, err_info, path_token */
	char *buf;
	size_t buf_s = 1024;
	db_t *db;
	token **cmds;

	(void)ac;
	db = create_database(&buf, buf_s, av[0], envp);
	if (db == NULL)
		exit(-1);

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		/* getline w/ prompt */
		if (isatty(STDIN_FILENO))
			_puts("$ ", 1);
		if (getline(&buf, &buf_s, stdin) == -1)
			break;
		/* create cmd_tokens */
		cmds = create_tokens(buf);
		if (cmds == NULL)
			break;
		/* execute cmd_tokens */
		exe_tokens(cmds, db);
		db->ln++;
		free_tokens(cmds);
	}

	exit(free_database(db));
}
