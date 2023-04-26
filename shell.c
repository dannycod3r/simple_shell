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

	signal(SIGINT, ignore_ctrlc);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			_puts("#cisfun$ ");

		/*Read user input*/
		if (getline(&input, &input_size, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				_puts("\n");
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
			execute_command(args, env, av);
	}

	free(input);
	return (EXIT_SUCCESS);
}

/**
 * execute_command - forks a child process and executes a command within it
 * @args: null-terminated array of command-line arguments
 * @env: null-terminated array of environment variables
 * @av: string of args
 * Return: On success, 0. On failure, -1.
 */
int execute_command(char **args, char **env, char **av)
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
		perror(av[0]);
		exit(EXIT_FAILURE);
	}
	else
	{

		/* Parent process: wait for child to finish*/
		waitpid(pid, &status, 0);
	}

	return (0);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - print to stdout
 * @s: string
 * Return: character
 */
int _puts(const char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		if (_putchar(s[i]) == EOF)
			return (EOF);
	return (0);
}

/**
 * ignore_ctrlc - ignore control C to exit the shell
 * @signal: signal
 * Return: void
 */
void ignore_ctrlc(int signal)
{
	if (signal == SIGINT)
	{
		_putchar('\n');
		_puts("#cisfun$ ");
	}
}
