#include "shell.h"

/**
 * custom_memset - sets a constant byte in a memory block
 * @memory: pointer to the memory block
 * @byte: the byte to set in the memory block
 * @size: the number of bytes to set
 * Return: a pointer to the modified memory block
 */
char *custom_memset(char *memory, char byte, unsigned int size)
{
unsigned int i;

for (i = 0; i < size; i++)
memory[i] = byte;
return (memory);
}

/**
 * custom_free_strings - releases memory allocated for an array of strings
 * @string_array: the array of strings to free
 */
void custom_free_strings(char **string_array)
{
char **temp = string_array;

if (!string_array)
return;
while (*string_array)
free(*string_array++);
free(temp);
}

/**
 * custom_reallocate - reallocates a block of memory with optional resizing
 * @prev_block: pointer to the previously allocated memory block
 * @prev_size: size of the previous memory block in bytes
 * @new_size: size of the new memory block in bytes
 *
 * Return: pointer to the reallocated memory block
 */
void *custom_reallocate(void *prev_block, unsigned int prev_size, unsigned int new_size)
{
char *new_block;

if (!prev_block)
return (malloc(new_size));
if (!new_size)
return (free(prev_block), NULL);
if (new_size == prev_size)
return (prev_block);

new_block = malloc(new_size);
if (!new_block)
return (NULL);

prev_size = prev_size < new_size ? prev_size : new_size;
while (prev_size--)
new_block[prev_size] = ((char *)prev_block)[prev_size];
free(prev_block);
return (new_block);
}

