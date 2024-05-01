#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
ssize_t custom_getline(char **lineptr, size_t *n);
void execute_command(char *command);

#endif /* SHELL_H */

