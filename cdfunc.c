#include "utils.h"

/**
 * change_directory - changes the current working directory
 * @dir: the directory to change to, NULL if none specified
 * Return: 0 on success, -1 on failure
 */
int change_directory(char *dir)
{
	char *cwd = NULL;
	int ret;

	if (dir == NULL || strcmp(dir, "~") == 0)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			fprintf(stderr, "cd: no home directory\n");
			return (-1);
		}
	}
	if (strcmp(dir, "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (dir == NULL)
		{
			fprintf(stderr, "cd: no previous directory\n");
			return (-1);
		}
		printf("%s\n", dir);
	}
	ret = chdir(dir);
	if (ret == -1)
	{
		perror("cd");
		return (-1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
	free(cwd);
	return (0);
}
