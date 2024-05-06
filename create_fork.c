#include "shell.h"

/**
 * execute_command - Executes a command by searching
 * for it in PATH directories.
 * @tokens: Null-terminated array of pointers to the command and its arguments.
 * @env: Null-terminated array of pointers to the environment variables.
 * @is_terminal: Flag indicating if the shell is running in interactive mode.
 * @shell_name: The name of the shell program.
 *
 * Return: 1 if the shell should continue running, 0 otherwise.
 */
int execute_command(char **tokens,
		char **env, int is_terminal, char *shell_name)
{
	char *full_file_name;
	char *path;
	char *exec_name;

	if (!tokens || !tokens[0])
		return (0);

	execve(tokens[0], tokens, env);

	path = get_path(env);
	full_file_name = split_path(tokens[0], path);

	if (full_file_name != NULL && path != NULL)
	{
		exec_name = tokens[0];

		tokens[0] = full_file_name;
		execve(tokens[0], tokens, env);
		tokens[0] = exec_name;
		free(full_file_name);
	}

	if (tokens != NULL && *tokens != NULL)
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
	return (0);
}

/**
 * create_fork - Creates a new process to execute a command.
 * @shell_name: The name of the shell program.
 * @tokens: Null-terminated array of pointers to
 * the command and its arguments.
 * @env: Null-terminated array of pointers to the environment variables.
 * @is_terminal: Flag indicating if the shell is running in interactive mode.
 *
 * This function creates a new process using the fork system call.
 * If the fork fails, it prints an error message and returns 0.
 * If the new process is a child process, it attempts to execute
 * the command specified in 'tokens' using the execve system call.
 * If the command is not found, it tries to find the command
 * in the directories specified in the PATH environment variable.
 * If the command is still not found, it handles the error
 * by printing an appropriate error message.
 * If the shell is running in interactive mode and the command
 * is not found, it prints "No such file or directory".
 * If the shell is not running in interactive mode and the command
 * is not found, it prints "1: [command]: not found".
 *
 * Return: 1 if the shell should continue running, 0 otherwise.
 */
int create_fork(char *shell_name, char **tokens, char **env, int is_terminal)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (0);
	} else if (child_pid == 0)
	{
		return (execute_command(tokens, env, is_terminal, shell_name));
	}
	else
	{
		wait(&status);
	}
	return (1);
}

