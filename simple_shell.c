#include "shell.h"
#include <string.h>

/**
 * custom_getline - Reads a line from the standard input.
 * @lineptr: A pointer to the buffer storing the read line.
 * @n: The size of the buffer.
 *
 * Return: Upon success, returns the number of bytes read, including the
 *         newline character. If an error occurs or end-of-file is reached,
 *         returns -1.
 */
ssize_t custom_getline(char **lineptr, size_t *n)
{
	return (getline(lineptr, n, stdin));
}

/**
 * execute_command - Executes a command in the shell.
 * @command: The command to execute.
 *
 * Return: void
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *envp[] = {NULL};

		if (execve(command, argv, envp) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
