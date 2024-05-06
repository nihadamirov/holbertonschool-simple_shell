#include "shell.h"

int create_fork(char *shell_name, char **tokens, char **env, int is_terminal)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Fork error");
        return (0);
    }
    else if (child_pid == 0)
    {
        execve(tokens[0], tokens, env);

        perror("Execve error");

        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);

        if (!WIFEXITED(status))
        {
            write(1, shell_name, _strlen(shell_name));
            if (is_terminal)
                write(1, ": No such file or directory\n", 28);
            else
            {
                write(1, ": 1: ", 5);
                write(1, tokens[0], _strlen(tokens[0]));
                write(1, ": not found\n", 12);
            }
        }
    }
    return (1);
}

