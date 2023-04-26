#include "simple_shell.h"

/**
 * main - program entry
 * @ac: int. arguement count
 * @argv: string. null terminated array of arguements
 * Return: 0
 */
int main(int ac, char **argv)
{
	char *token;
	char *input = NULL, *input_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0, i;

	(void)ac;

	while (1)
	{
		printf("#cisfun$ ");
		nchars_read = getline(&input, &n, stdin);
		/* c*/
		if (nchars_read == -1)
			return (-1);

		/* allocate space for a copy of the input */
		input_copy = malloc(sizeof(char) * nchars_read);
		if (input_copy == NULL)
		{
			perror("mem alloc error");
			return (-1);
		}
		/* copy input to input_copy */
		strcpy(input_copy, input);

		token = strtok(input, delim);
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* Allocate space to hold the array of strings */
		argv = malloc(sizeof(char *) * num_tokens);

		/* Store each token in the argv array */
		token = strtok(input_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		/* execute the command */
		execmd(argv);

	}


	/* free up allocated memory */
	free(input_copy);
	free(input);

	return (0);
}


/**
 * execmd - executes a given command
 * @argv: array of strings containing command and its args
 * Return: void
 */

void execmd(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		/* get the command */
		command = argv[0];

		/* execute the command with execve */
		if (execve(command, argv, NULL) == -1)
			perror(command);
	}

}
