#include <stddef.h>
#include <stdlib.h>
/**
 * my_strcmp - compare two strings
 *
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: integer value indicating result of comparison
 */
int my_strcmp(const char *s1, const char *s2)
{
	int i = 0;
	unsigned char u1, u2;

	if (s1 == NULL || s2 == NULL)
	{
		return (-1 * (s1 == NULL) + (s2 == NULL));
	}

	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}

	u1 = (unsigned char) s1[i];
	u2 = (unsigned char) s2[i];

	return (u1 - u2);
}
