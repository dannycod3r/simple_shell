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
	int i;

/*Print the command-line arguments*/
	printf("Command-line arguments:\n");
	for (i = 0; i < ac; i++)
	{
		printf("  av[%d]: %s\n", i, av[i]);
	}

/*Print the environment variables*/
	printf("Environment variables:\n");
	for (i = 0; env[i] != NULL; i++)
	{
		printf("  env[%d]: %s\n", i, env[i]);
	}

	return (0);
}
