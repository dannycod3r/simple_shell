#ifndef _UTILS_H
#define _UTILS_H
/*utils.h - includes declarations for all helper functions*/

int execute_command(char **args, char **env, char **av);

void ignore_ctrlc(int signal);

int _puts(const char *s);
int _putchar(char c);

#endif  /*_UTILS_H*/
