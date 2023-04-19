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
	int status, argc;
	pid_t pid;

	(void)ac;
	(void)av;

	while (1)
	{
		printf("#cisfun$ ");

		/*Read user input*/
		if (getline(&input, &input_size, stdin) == -1)
			break; /*Exit if EOF or error*/

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
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
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
		}
	}

	free(input);
	return (EXIT_SUCCESS);
}
