#include <stdlib.h>
#include <stdio.h>

/**
 * unset_env - unset environment variable
 * @name: name of variable
 *
 * Return: 0 on success else -1
 */
int unset_env(char *name)
{
	int result = unsetenv(name);

	if (name == NULL || name[0] == '\0')
	{
		fprintf(stderr, "unsetenv: invalid argument\n");
		return (-1);
	}
	if (result < 0)
	{
		fprintf(stderr, "unsetenv: failed to unset %s\n", name);
		return (-1);
	}
	return (0);
}
