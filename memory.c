#include "shell.h"

/**
 * freeAndNull - Deallocates memory pointed to by a pointer and sets it to NULL.
 * @ptr: Pointer to the memory to be deallocated.
 *
 * This function frees the memory pointed to by 'ptr' and then sets 'ptr' to NULL
 * to prevent any accidental use of the freed memory.
 *
 * Return: 1 if memory was freed, 0 otherwise.
 */
int freeAndNull(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}

