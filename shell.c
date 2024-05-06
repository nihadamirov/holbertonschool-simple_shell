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
	int status = 1;
	char *stdin_line = NULL;
        size_t buffsize = 0;
        int is_terminal = isatty(0);
	ssize_t bytes_read;
	char **line_tokens;
	int special_case;

	while (status)
	{

        if (is_terminal)
            write(1, "$ ", 2);

        bytes_read = getline(&stdin_line, &buffsize, stdin);

        if (bytes_read == -1)
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

        free(stdin_line);
        free(line_tokens);

        if (special_case == 0)
            return (EXIT_SUCCESS);

        if (special_case == 1)
            continue;

        status = create_fork(argv[0], line_tokens, env, is_terminal);
	}

    return (EXIT_SUCCESS);
}

