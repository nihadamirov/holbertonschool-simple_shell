#include "shell.h"

/**
 * create_child_process - Creates a new child process.
 *
 * This function creates a new child process using the fork system call.
 * If the fork fails, it prints an error message and terminates the program.
 *
 * Return: The process ID of the child process if the fork is successful,
 * otherwise it terminates the program.
 */
pid_t create_child_process(void)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	return (child_pid);
}

/**
 * execute_command - Executes a command.
 * @tokens: Null-terminated array of pointers to the command and its arguments.
 * @env: Null-terminated array of pointers to the environment variables.
 *
 * This function attempts to execute the command specified in 'tokens'
 * using the execve system call.
 * If 'tokens' is NULL or if the first element of 'tokens' is NULL,
 * the function terminates the program.
 */
void execute_command(char **tokens, char **env)
{
	if (!tokens || !tokens[0])
		exit(EXIT_FAILURE);

	execve(tokens[0], tokens, env);
}

/**
 * handle_command_not_found - Handles the case when a command is not found.
 * @shell_name: The name of the shell program.
 * @tokens: Null-terminated array of pointers to the command and its arguments.
 * @is_terminal: Flag indicating if the shell is running in interactive mode.
 *
 * This function prints an error message to the standard output
 * when a command is not found.
 * The format of the error message depends on whether the shell
 * is running in interactive mode.
 * After printing the error message, the function terminates the program.
 */
void handle_command_not_found(char *shell_name, char **tokens, int is_terminal)
{
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
	exit(EXIT_FAILURE);
}

/**
 * create_fork - Creates a new process to execute a command.
 * @shell_name: The name of the shell program.
 * @tokens: Null-terminated array of pointers to the command and its arguments.
 * @env: Null-terminated array of pointers to the environment variables.
 * @is_terminal: Flag indicating if the shell is running in interactive mode.
 *
 * This function creates a new process using the
 * create_child_process function.
 * If the new process is a child process, it attempts to execute
 * the command specified in 'tokens'
 * using the execute_command function.
 * If the command is not found, it tries to find the command
 * in the directories specified in the PATH environment variable.
 * If the command is still not found,
 * it handles the error using the handle_command_not_found function.
 *
 * Return: 1 if the shell should continue running, 0 otherwise.
 */
int create_fork(char *shell_name, char **tokens, char **env, int is_terminal)
{
	pid_t child_pid;
	int status;

	child_pid = create_child_process();

	if (child_pid == 0)
	{
		char *full_file_name;
		char *path;

		execute_command(tokens, env);

		path = get_path(env);
		full_file_name = split_path(tokens[0], path);

		if (full_file_name != NULL && path != NULL)
		{
			char *exec_name = tokens[0];

			tokens[0] = full_file_name;
			execute_command(tokens, env);
			tokens[0] = exec_name;
			free(full_file_name);
		}

		handle_command_not_found(shell_name, tokens, is_terminal);
	}
	else
	{
		wait(&status);
	}
	return (1);
}
