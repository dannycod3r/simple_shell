#include <stdio.h>
#include <stdlib.h>

/**
 * set_env - set environment variable or create new variable
 * @name: name of variable
 * @value: value of variable
 * Return: 0 on success, -1 on failure
 */
int set_env(char *name, char *value)
{
	int result = setenv(name, value, 1);

	if (name == NULL || name[0] == '\0' || value == NULL)
	{
		fprintf(stderr, "setenv: invalid arguments\n");
		return (-1);
	}
	if (result < 0)
	{
		fprintf(stderr, "setenv: failed to set %s=%s\n", name, value);
		return (-1);
	}
	return (0);
}
