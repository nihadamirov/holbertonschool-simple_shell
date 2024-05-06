#include "shell.h"
#include <stdio.h>

/**
 * main - Main function for the shell.
 *
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * @env: Array of pointers to the environment variables.
 * Return: EXIT_SUCCESS upon successful execution.
 */
int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	int status = 1;
	char *stdin_line = NULL;
	size_t buffsize = 0;

	while (status)
	{
		char **line_tokens = NULL;
		int is_terminal;
		int special_case;

		is_terminal = isatty(0);
		if (is_terminal)
			write(1, "$ ", 2);

		if (getline(&stdin_line, &buffsize, stdin) == -1)
			break;

		line_tokens = str_tokens(stdin_line);
		if (!line_tokens)
			break;

		special_case = special_cases(line_tokens, argv[0], env);

		if (special_case == 0)
		{
			free(stdin_line);
			free(line_tokens);
			return (EXIT_SUCCESS);
		}
		else if (special_case == 1)
		{
			free(line_tokens);
			continue;
		}

		status = create_fork(argv[0], line_tokens, env, is_terminal);

		free(line_tokens);
	}

	free(stdin_line);
	return (EXIT_SUCCESS);
}

