#include "shell.h"

/**
 * execute_Args - Excutes commands found in input path
 * @cmd: Pointer to array of parsed command strings
 * @input: Cmd input string
 * @c:Shell Exec Time Case of Command Not Found
 * @argv: Argument array vector
 * Return: 1 if cmd Null -1 Wrong Command 0 Execution Success
 */
int execute_Args(char **cmd, char *input, int c, char **argv)
{
	int wstatus;
	pid_t pid;

	if (*cmd == NULL)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to start process. Exiting...");
		return (-1);
	}
	if (pid == 0)
	{
		if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
			find_path_dir(cmd);
		if (access(cmd[0], R_OK) != 0)
		{
			_perror(cmd[0], c, argv);
			free_all(cmd, input);
			exit(127);
		}
		if (execve(*cmd, cmd, environ) == -1)
			return (2);
		else
			return (0);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) == 0)
			return (0);
		else if (WEXITSTATUS(wstatus) == 2)
			return (2);
		else if (WEXITSTATUS(wstatus) == 127)
			return (127);
	}
	return (127);
}

/**
 * handle_signal - Configures ^C not to terminate our shell
 * @sig: Incoming Signal
 */
void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		PRINT("\n$ ");
	}
}
