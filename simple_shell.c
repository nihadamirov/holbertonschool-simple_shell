#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
	ssize_t read_bytes = getline(lineptr, n, stdin);

	if (read_bytes == (-1))
	{
		perror("getline");
	}
	return (read_bytes);
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
 	
	if (execvp(command, argv) == -1)
        {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
}

