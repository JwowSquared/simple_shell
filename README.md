# simple_shell #
A simple command line interpreter from Jacob and Jacob, which is totally not a
law firm, I swear.

# Directory #
/simple_shell/
*	AUTHORS - authors of this program
*	README.md - this file
*	builtins_1.c - Builtins file #1, containing builtins exit, env, setenv,
		       and unsetenv plus supporting function findenvi
*	builtins_2.c - Builtins file #2, containing builtins cd plus supporting
		       functions getenv_value and update_env
*	copy_aos.c - file for copy_aos functionality for the purpose of handling
	             the environment variables list, contains copy_aos and
		     free_aos functions
*	header_shell.h - main header file containing all includes and prototypes
		         plus the command_token and builtin_dictionary structs
*	main_shell.c - main file, containing main, check_builtin, and
		       setup_buffers functions
*	pathing.c - file containg PATH handeling functionality including
		    fix_path function
*	shell_man - manual for the Simple Shell
*	token.c - file for handling command_token structs, containing
		  create_token, count_arguments, and free_token functions
*	utilities_1.c - Utilities file #1, containing utility functions _atoi,
		        _putchar, _strcat, and _strcmp
*	utlities_2.c - Utilities file #2, containing utility function
		       print_string