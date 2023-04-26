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
	char *input = NULL, *args[MAX_ARGS], *token, *path_env, *full_path;
	size_t input_size = 0;
	int status, argc, found_executable, exit_status = 0;
	pid_t pid;
	path_t *head = NULL, *current_path;

	(void)ac;
	(void)av;

	/*parse PATH env to linked list*/
	path_env = getenv("PATH");
	if (path_env != NULL)
	{
		token = strtok(path_env, ":");
		while (token != NULL)
		{
			head = add_path(&head, token);
			token = strtok(NULL, ":");
		}
	}

	while (1)
	{
		printf("#cisfun$ ");

		/*Read user input*/
		/* Implement custome getline function */
		if (custom_getline(&input, &input_size, stdin) == -1)
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

		/* Implement exit built-in function with arguments */
		if (argc > 0 && strcmp(args[0], "exit") == 0)
		{
			if (argc > 1)
				exit_status = atoi(args[1]);
			else
				exit_status = EXIT_SUCCESS;
			break;
		}

		/* Implement setenv built in function */
		if (argc > 2 && strcmp(args[0], "setenv") == 0)
			if (set_env(args[1], args[2]) != 0)
				fprintf(stderr, "Failed to set environment variable.\n");

		/* Implement unsetenv built in function */
		if (argc > 1 && strcmp(args[0], "unsetenv") == 0)
			if (unset_env(args[1]) != 0)
				fprintf(stderr, "Failed to unset environment variable.\n");

		/* Implement the cd built in function */
		if (argc > 0 && strcmp(args[0], "cd") == 0)
		{
			if (argc > 2)
			{
				fprintf(stderr, "cd: too many arguments\n");
				continue;
			}

			if (change_directory(argc == 1 ? NULL : args[1]) == -1)
				perror("cd");

			continue;
		}

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
				found_executable = 0;
				if (args[0][0] == '/')
				{
					if (access(args[0], X_OK) == 0)
						found_executable = 1;
				}
				else
				{
					current_path = head;
					while (current_path != NULL)
					{
						full_path = malloc(strlen(current_path->path) + strlen(args[0]) + 2);
						sprintf(full_path, "%s/%s", current_path->path, args[0]);
						if (access(full_path, X_OK) == 0)
						{
							/*Found executable in PATH directory*/
							args[0] = full_path;
							found_executable = 1;
							break;
						}
						free(full_path);
						current_path = current_path->next;
					}
				}
				if (found_executable)
				{
					execve(args[0], args, env);
					perror("exec");
					exit(EXIT_FAILURE);
				}
				else
				{
					/*Could not find executable in PATH directories*/
					printf("Command not found: %s\n", args[0]);
					exit(EXIT_FAILURE);
				}
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
	/*free memory*/
	free_path(head);

	free(input);
	/* handle arguments for the in-built exit function */
	return (exit_status);
}
