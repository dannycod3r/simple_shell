#ifndef _SIMPLE_SHELL_H
#define _SIMPLE_SHELL_H
/*simple_shell.h - includes all other header files*/

#include "constants.h"
#include "libs.h"
#include "utils.h"

/*program entry point*/
int main(int ac, char **av, char **env);

int change_directory(char *dir); /* change directory function */

char *my_getline(void); /* getline function */

int set_env(char *name, char *value);

int unset_env(char *name);

#endif /*_SIMPLE_SHELL_H*/
