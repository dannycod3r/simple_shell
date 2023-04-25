#include "libs.h"
/**
 * custom_getline - read input from specified input stream and stores in buffer
 * @input: pointer to a pointer that will store the input string.
 * @input_size: pointer to variable that stores the size of input string.
 * @stream: pointer to the input stream from which to read the input.
 * Return: number of characters read, including the newline character,
 * and -1 if an error occurs.
 */
int custom_getline(char **input, size_t *input_size, FILE *stream)
{
	static char *buff;
	static size_t buff_size;
	static size_t buff_index;
	int c;
	size_t num_chars = 0, result_index;
	char *result = malloc(buff_index + 1);

	if (input == NULL || input_size == NULL || stream == NULL)
		return (-1);

	if (buff == NULL)
	{
		buff_size = BUFSIZ;
		buff = malloc(buff_size);
	}

	while ((c = fgetc(stream)) != EOF)
	{
		if (buff_index >= buff_size)
		{
			buff_size += BUFSIZ;
			buff = realloc(buff, buff_size);
		}

		buff[buff_index++] = (char) c;
		num_chars++;
		if (c == '\n')
			break;
	}
	if (buff_index == 0 && c == EOF)
		return (-1);

	buff[buff_index] = '\0';
	*input = buff;
	*input_size = buff_index;
	for (result_index = 0; result_index < buff_index; result_index++)
		result[result_index] = buff[result_index];
	result[result_index] = '\0';

	buff_index = 0;
	*input = result;
	*input_size = num_chars;

	return ((int) num_chars);
}
