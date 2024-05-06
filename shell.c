#include "shell.h"
#include <stdio.h>

/**
 * read_line - Reads a line from stdin.
 *
 * Return: Allocated buffer containing the line read from stdin.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);

	return (line);
}

/**
 * parse_line - Parses a line into tokens.
 *
 * @line: The line to parse.
 * Return: Array of tokens.
 */
char **parse_line(char *line)
{
	return (str_tokens(line));
}

/**
 * handle_special_cases - Handles special cases like "exit" or "env".
 *
 * @tokens: Array of tokens representing the command and its arguments.
 * @shell_name: Name of the shell program.
 * @env: Array of pointers to the environment variables.
 * Return: 0 if the shell should exit, 1 if the shell
 * should continue, 2 if neither.
 */
int handle_special_cases(char **tokens, char *shell_name, char **env)
{
	return (special_cases(tokens, shell_name, env));
}

/**
 * execute_command - Executes a command in a new process.
 *
 * @shell_name: Name of the shell program.
 * @tokens: Array of tokens representing the command and its arguments.
 * @env: Array of pointers to the environment variables.
 * @is_terminal: Flag indicating if the shell is running in interactive mode.
 * Return: 1 if the shell should continue running, 0 otherwise.
 */
int execute_command(char *shell_name,
		char **tokens, char **env, int is_terminal)
{
	return (create_fork(shell_name, tokens, env, is_terminal));
}

/**
 * main - Main function for the shell.
 *
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * @env: Array of pointers to the environment variables.
 * Return: EXIT_SUCCESS upon successful execution.
 */
int main(int argc, char **argv, char **env)
{
	int status = 1;
	char *stdin_line;
	char **line_tokens;
	int special_case;

	while (status)
	{
		stdin_line = read_line();
		if (!stdin_line)
			break;

		line_tokens = parse_line(stdin_line);
		if (!line_tokens)
		{
			free(stdin_line);
			break;
		}
		special_case = handle_special_cases(line_tokens, argv[0], env);

		if (special_case == 0)
		{
			free(stdin_line);
			free(line_tokens);

			return (EXIT_SUCCESS);
		} else if (special_case == 1)
		{
			free(stdin_line);
			free(line_tokens);

			continue;
		}

		is_terminal = isatty(0);
		status = execute_command(argv[0], line_tokens, env, is_terminal);

		free(stdin_line);
		free(line_tokens);
	}
	return (EXIT_SUCCESS);
}

