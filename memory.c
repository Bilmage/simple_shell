#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL
 * @ptr: Pointer to the memory to be released
 *
 * This function frees the memory pointed to by `ptr` and then sets `ptr` to NULL.
 *
 * Return: 1 if memory was freed, 0 otherwise.
 */
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}

