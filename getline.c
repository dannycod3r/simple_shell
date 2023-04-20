#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * my_getline - Read a line of text from standard input
 *
 * Return: A pointer to the line of text, or NULL if end of file is reached
 */
char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_index = 0;
	static int buffer_size = 0;
	char *line = NULL;
	int line_index = 0;
	/*int read_size = 0;*/

	while (1)
	{
		/* Check if we need to read more data into the buffer */
		if (buffer_index >= buffer_size)
		{
			buffer_index = 0;
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (buffer_size == 0)
			{
				/* End of file reached */
				if (line_index == 0)
				{
					return (NULL);
				}
				else
				{
					break;
				}
			}
			if (buffer_size < 0)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
		}
		/* Check if we need to allocate more memory for the line */
		if (line_index == 0)
		{
			line = (char *) malloc(BUFFER_SIZE);
		}
		else if (line_index % BUFFER_SIZE == 0)
		{
			line = (char *) realloc(line, line_index + BUFFER_SIZE);
		}
		/* Copy characters from the buffer to the line until we reach a newline or the end of the buffer */
		while (buffer_index < buffer_size)
		{
			if (buffer[buffer_index] == '\n')
			{
				line[line_index] = '\0';
				buffer_index++;
				return (line);
			}
			else
			{
				line[line_index] = buffer[buffer_index];
				line_index++;
				buffer_index++;
			}
		}
	}
	/* Null terminate the line and return it */
	line[line_index] = '\0';
	return (line);
}
