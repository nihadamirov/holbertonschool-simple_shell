#include "shell.h"
#include <stdio.h>

/**
 * main - Entry point of the program.
 *
 * Description: This function serves as the entry point of the shell program.
 * It reads commands from the standard input, executes them, and prints the
 * results to the standard output.
 *
 * Return: Always returns 0 to indicate successful completion.
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;
	
	while (1)
	{
        printf("($) ");
        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1)
        {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        execute_command(buffer);
    }
    free(buffer);
    return 0;
}

