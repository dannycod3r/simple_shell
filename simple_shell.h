#ifndef _SIMPLE_SHELL_H
#define _SIMPLE_SHELL_H
/*simple_shell.h - includes all other header files*/

#include "constants.h"
#include "libs.h"
#include "utils.h"

/*program entry point*/
int main(int ac, char **av, char **env);

int set_env(char *name, char *value);

path_t *add_path(path_t **head, char *token);

void free_path(path_t *head);


int custom_getline(char **input, size_t *input_size, FILE *stream);

int change_directory(char *dir);

int unset_env(char *name);

int my_strcmp(const char *s1, const char *s2);



#endif /*_SIMPLE_SHELL_H*/
