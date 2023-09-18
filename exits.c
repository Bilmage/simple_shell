#include "shell.h"

/**
 * my_strncpy - Copy a portion of one string to another.
 * @dest: The destination string where data is copied.
 * @src: The source string from which data is copied.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
size_t i;

for (i = 0; i < n && src[i] != '\0'; i++)
{
dest[i] = src[i];
}

while (i < n)
{
dest[i++] = '\0';
}

return (dest);
}

/**
 * my_strncat - Concatenate two strings with a maximum limit.
 * @dest: The destination string where data is concatenated.
 * @src: The source string to be concatenated.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the destination string.
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
size_t dest_len = strlen(dest);
size_t i;

for (i = 0; i < n && src[i] != '\0'; i++)
{
dest[dest_len + i] = src[i];
}

dest[dest_len + i] = '\0';

return (dest);
}

/**
 * my_strchr - Locate a character in a string.
 * @s: The string to search within.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the character 'c' in 's', or NULL if not found.
 */
char *my_strchr(const char *s, int c)
{
while (*s != '\0')
{
if (*s == c)
{
return ((char *)s);
}
s++;
}

if (c == '\0')
{
return ((char *)s);
}

return (NULL);
}

