#include "shell.h"

/**
 * Function: tokenizeStringR
 * Description: Tokenizes a string using a specified delimiter and maintains the
 *              state for subsequent tokenization calls.
 * @string: The string to be tokenized.
 * @delim: The delimiter used for tokenization.
 * @save_ptr: A pointer to keep track of the next available token.
 *
 * Return: The next available token.
 */
char *tokenizeStringR(char *string, char *delim, char **save_ptr)
{
char *finish;

if (string == NULL)
string = *save_ptr;

if (*string == '\0')
{
*save_ptr = string;
return (NULL);
}

string += skipDelimiters(string, delim);
if (*string == '\0')
{
*save_ptr = string;
return (NULL);
}

finish = string + findDelimiterEnd(string, delim);
if (*finish == '\0')
{
*save_ptr = finish;
return (string);
}

*finish = '\0';
*save_ptr = finish + 1;
return (string);
}

/**
 * Function: stringToInteger
 * Description: Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer.
 */
int stringToInteger(char *s)
{
unsigned int n = 0;

do {
if (*s == '-')
return (-1);
else if ((*s < '0' || *s > '9') && *s != '\0')
return (-1);
else if (*s >= '0'  && *s <= '9')
n = (n * 10) + (*s - '0');
else if (n > 0)
break;
} while (*s++);
return (n);
}

/**
 * Function: reallocateMemory
 * Description: Reallocates a memory block to a new size.
 * @ptr: Pointer to the memory previously allocated with malloc.
 * @old_size: The size of the original memory block.
 * @new_size: The size of the new memory block to be allocated.
 *
 * Return: Pointer to the address of the new memory block.
 */
void *reallocateMemory(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *temp_block;
unsigned int i;

if (ptr == NULL)
{
temp_block = allocateMemory(new_size);
return (temp_block);
}
else if (new_size == old_size)
return (ptr);
else if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}
else
{
temp_block = allocateMemory(new_size);
if (temp_block != NULL)
{
for (i = 0; i < minimum(old_size, new_size); i++)
*((char *)temp_block + i) = *((char *)ptr + i);
free(ptr);
return (temp_block);
}
else
return (NULL);

}
}

/**
 * Function: handleCtrlC
 * Description: Handles the signal raised by pressing CTRL-C.
 * @signum: The signal number.
 *
 * Return: Void.
 */
void handleCtrlC(int signum)
{
if (signum == SIGINT)
print("\n($) ", STDIN_FILENO);
}

/**
 * Function: ignoreComment
 * Description: Removes or ignores everything after a '#' character in the input.
 * @input: The input string to be processed.
 *
 * Return: Void.
 */
void ignoreComment(char *input)
{
int i = 0;

if (input[i] == '#')
input[i] = '\0';
while (input[i] != '\0')
{
if (input[i] == '#' && input[i - 1] == ' ')
break;
i++;
}
input[i] = '\0';
}

