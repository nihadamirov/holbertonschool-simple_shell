#include "shell.h"
#include <stdio.h>

/**
 * read_line - Reads a line from the standard input.
 * @stdin_line: Pointer to the line read from the standard input.
 * @buffsize: Pointer to the size of the buffer.
 *
 * This function reads a line from the standard input using
 * the getline function.
 * If getline fails to read a line, the function frees 'stdin_line' and
 * terminates the program.
 */
void read_line(char **stdin_line, size_t *buffsize)
{
	*stdin_line = NULL;
	if (getline(stdin_line, buffsize, stdin) == -1)
	{
		free(*stdin_line);
		exit(EXIT_SUCCESS);
	}
}

/**
 * tokenize_line - Tokenizes a line.
 * @stdin_line: The line to be tokenized.
 *
 * This function tokenizes 'stdin_line' using the str_tokens function.
 * If str_tokens fails to tokenize the line, the function frees 'stdin_line'
 * and terminates the program.
 *
 * Return: A null-terminated array of pointers to the tokens.
 */
char **tokenize_line(char *stdin_line)
{
	char **line_tokens = str_tokens(stdin_line);

	if (!line_tokens)
	{
		free(stdin_line);
		exit(EXIT_SUCCESS);
	}
	return (line_tokens);
}

/**
 * handle_special_cases - Handles special cases.
 * @line_tokens: Null-terminated array of pointers to the tokens.
 * @shell_name: The name of the shell program.
 * @env: Null-terminated array of pointers to the environment variables.
 *
 * This function handles special cases using the special_cases function.
 * If 'line_tokens' is a special case, the function frees 'line_tokens' and
 * terminates the program if necessary.
 *
 * Return: The return value of the special_cases function.
 */
int handle_special_cases(char **line_tokens, char *shell_name, char **env)
{
	int special_case;

	special_case = special_cases(line_tokens, shell_name, env);
	if (special_case == 0 || special_case == 1)
	{
		free(line_tokens[0]);
		free(line_tokens);
		if (special_case == 0)
			exit(EXIT_SUCCESS);
	}
	return (special_case);
}

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
	int status = 1;
	size_t buffsize = 100;
	char *stdin_line;
	char **line_tokens;
	int is_terminal = isatty(0);

	while (status)
	{
		if (is_terminal)
			write(1, "$ ", 2);

		read_line(&stdin_line, &buffsize);
		line_tokens = tokenize_line(stdin_line);
		handle_special_cases(line_tokens, argv[0], env);
		status = create_fork(argv[0], line_tokens, env, is_terminal);

		free(stdin_line);
		free(line_tokens);
	}
	return (EXIT_SUCCESS);
}

