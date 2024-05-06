#include "shell.h"
#include <stdio.h>

/**
 * main - Main driver for the shell.
 * @argc: Argument count (unused in this function).
 * @argv: Array containing the program name.
 * @env: Array containing the environment variables.
 *
 * This function reads and executes user-inputted commands.
 * It reads the line entered by the user,
 * tokenizes the line, checks for special cases
 * (e.g., "exit" and "env" commands), and then creates
 * a new process for the execution of the command.
 * This process continues until the user enters the "exit" command.
 *
 * Return: EXIT_SUCCESS, if the driver terminates successfully.
 */
int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	int status = 1;

	size_t buffsize;
	char *stdin_line;

	while (status)
	{
		char **line_tokens = NULL;
		int is_terminal;
		int special_case;

		buffsize = 100;
		stdin_line = NULL;

		is_terminal = isatty(0);
		if (is_terminal)
			write(1, "$ ", 2);

		if (getline(&stdin_line, &buffsize, stdin) == -1)
		{
			free(stdin_line);
			break;
		}

		line_tokens = str_tokens(stdin_line);
		if (!line_tokens)
		{
			free(stdin_line);
			break;
		}

		special_case = special_cases(line_tokens, argv[0], env);

		/* exit */
		if (special_case == 0)
		{
			free(stdin_line);
			free(line_tokens);
			return (EXIT_SUCCESS);
		}
		/* env */
		else if (special_case == 1)
		{
			free(stdin_line);
			free(line_tokens);
			continue;
		}

		status = create_fork(argv[0], line_tokens, env, is_terminal);

		free(stdin_line);
		free(line_tokens);
	}

	return (EXIT_SUCCESS);
}

