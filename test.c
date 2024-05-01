#include "shell.h"
#include <stdio.h>

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while (1)
    {
        printf("#cisfun$ ");
        characters = custom_getline(&buffer, &bufsize);
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

