#ifndef _UTILS_H
#define _UTILS_H

#include "constants.h"
#include "libs.h"
/*utils.h - includes declarations for all helper functions*/
int custom_getline(char **input, size_t *input_size, FILE *stream);

/* change directory function */
int change_directory(char *dir);

int set_env(char *name, char *value);

int unset_env(char *name);

/*linked list for PATH*/
void free_path(path_t *head);
path_t *add_path(path_t **head, char *token);

#endif  /*_UTILS_H*/
