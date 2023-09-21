#include "shell.h"

/**
 **_copy_partial_string - copies a portion of a string
 *@dest: the destination string to copy to
 *@src: the source string
 *@n: the number of characters to copy
 *Return: a pointer to the copied string
 */
char *_copy_partial_string(char *dest, char *src, int n)
{
int i, j;
char *result = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;

if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (result);
}

/**
 **_concatenate_partial_strings - concatenates two strings up to a specified length
 *@dest: the first string
 *@src: the second string
 *@n: the maximum number of bytes to concatenate
 *Return: a pointer to the concatenated string
 */
char *_concatenate_partial_strings(char *dest, char *src, int n)
{
int i, j;
char *result = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (result);
}

/**
 **_find_character_in_string - locates a character in a given string
 *@s: the string to search within
 *@c: the character to locate
 *Return: a pointer to the first occurrence of the character in the string, or NULL if not found
 */
char *_find_character_in_string(char *s, char c)
{
do
{
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}

