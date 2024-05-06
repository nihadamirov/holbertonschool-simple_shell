#include "shell.h"
#include <stdio.h>

/**
 * main - Main driver for the shell.
 * @argc: Argument count (unused in this function).
 * @argv: Array containing the program name.
 * @env: Array containing the environment variables.
 *
 * This function reads and executes user-inputted commands.
 * It reads a line from the standard input, tokenizes the line,
 * handles special cases, and then creates a new process
 * for the execution of the command.
 * This process continues until the user enters the "exit" command.
 *
 * Return: EXIT_SUCCESS, if the driver terminates successfully.
 */
int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	size_t buffsize = 100;
	char *stdin_line = NULL;
	int special_case;
	int status;

	while (1)
	{
		char **line_tokens = NULL;
		int is_terminal = isatty(0);

		if (is_terminal)
			write(1, "$ ", 2);

		if (getline(&stdin_line, &buffsize, stdin) == -1)
			break;

		line_tokens = str_tokens(stdin_line);
		if (!line_tokens)
			break;

		special_case = special_cases(line_tokens, argv[0], env);

		if (special_case == 0)
			break;
		else if (special_case == 1)
			continue;

		status = create_fork(argv[0], line_tokens, env, is_terminal);

		if (status != 1)
			break;
	}

	free(stdin_line);
	return (EXIT_SUCCESS);
}
