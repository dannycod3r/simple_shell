#include "simple_shell.h"

/*linked list node for PATH dir*/
typedef struct path_n {
	char *path;
	struct path_n *next;
} path_t;

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
	int status, argc, found_executable;
	pid_t pid;
	path_t *head = NULL, *new_path, *next_path, *current_path;

	(void)ac;
	(void)av;

	/*parse PATH env to linked list*/
	path_env = getenv("PATH");
	if (path_env != NULL)
	{
		token = strtok(path_env, ":");
		while (token != NULL)
		{
			new_path = malloc(sizeof(path_t));
			new_path->path = strdup(token);
			new_path->next = head;
			head = new_path;
			token = strtok(NULL, ":");
		}
	}

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
				found_executable = 0;
				current_path = head;
				while (current_path != NULL)
				{
					full_path = malloc(strlen(current_path->path) + strlen(args[0]) + 2);
					sprintf(full_path, "%s/%s", current_path->path, args[0]);
					if (access(full_path, X_OK) == 0) {
						/*Found executable in PATH directory*/
						args[0] = full_path;
						found_executable = 1;
						break;
					}
					free(full_path);
					current_path = current_path->next;
				}
				if (found_executable) {
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
	current_path = head;
	while (current_path != NULL)
	{
		next_path = current_path->next;
		free(current_path->path);
		free(current_path);
		current_path = next_path;
	}

	free(input);
	return (EXIT_SUCCESS);
}
