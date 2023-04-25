#include "utils.h" /*function prtotype*/

/**
 * add_path - add path the PATH list
 * @head: path_t. starting path
 * @token: string. command string
 * Return: path.
 */
path_t *add_path(path_t **head, char *token)
{
	path_t *new_path = malloc(sizeof(path_t));

	new_path->path = strdup(token);
	new_path->next = *head;
	*head = new_path; /*hold the address*/

	return (*head);
}

/**
 * free_path - free memory allocated by path.
 * @head: path_t. entry point of the list
 * Return: nothing
 */
void free_path(path_t *head)
{
	path_t *current_path, *next_path;

	current_path = head;

	while (current_path != NULL)
	{
		next_path = current_path->next;
		free(current_path->path);
		free(current_path);
		current_path = next_path;
	}
}
