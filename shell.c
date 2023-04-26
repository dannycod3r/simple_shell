#include "simple_shell.h"

/**
 * main - program entry
 * @ac: int. arguement count
 * @av: string. null terminated array of arguements
 * @env: string. null terminated array of arguements
 * Return: 0
 */
int main(int ac, char **av, char **env)
{
	char *input = NULL, *args[MAX_ARGS], *token;
	size_t input_size = 0;
	int argc;

	(void)ac;
	(void)av;

	while (1)
	{
		printf("#cisfun$ ");

		/*Read user input*/
		if (getline(&input, &input_size, stdin) == -1)
		{
			printf("\n");
			break; /*Exit if EOF or error*/
		}

		/* Parse input into arguments*/
		argc = 0;
		token = strtok(input, " \t\n");
		while (token != NULL && argc < MAX_ARGS - 1)
		{
			args[argc++] = token;
			token = strtok(NULL, " \t\n");
		}
		args[argc] = NULL;

		/* Execute command*/
		if (argc > 0)
			execute_command(args, env);
	}

	free(input);
	return (EXIT_SUCCESS);
}

/**
 * execute_command - forks a child process and executes a command within it
 * @args: null-terminated array of command-line arguments
 * @env: null-terminated array of environment variables
 *
 * Return: On success, 0. On failure, -1.
 */
int execute_command(char **args, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process: execute command*/
		execve(args[0], args, env);
		perror("exec");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process: wait for child to finish*/
		waitpid(pid, &status, 0);
	}

	return (0);
}

