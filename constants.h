#ifndef _CONSTANTS_H
#define _CONSTANTS_H
/*constant.h - includes macros, constants and typedefs*/
#define MAX_ARGS 10

#define MAX_PATHS 1024

#define BUFFER_SIZE 1024

/*linked list node for PATH dir*/
/**
 * struct path_n- node structure for path
 * @path: string. path
 * @next: struct path_n. next path
 */
typedef struct path_n
{
	char *path;
	struct path_n *next;
} path_t;

#endif /*_CONSTANTS_H*/
