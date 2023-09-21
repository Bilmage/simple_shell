#include "shell.h"

/**
 * custom_strlen - Computes the length of a string.
 * @s: The string to be measured.
 *
 * Return: The length of the string as an integer.
 */
int custom_strlen(char *s)
{
int length = 0;

if (!s)
return (0);

while (*s++)
length++;
return (length);
}

/**
 * custom_strcmp - Performs a lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: A negative value if s1 < s2, a positive value if s1 > s2, and 0 if s1 == s2.
 */
int custom_strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
 * custom_starts_with - Checks if a string starts with a specified substring.
 * @haystack: The string to search within.
 * @needle: The substring to find.
 *
 * Return: A pointer to the character following the prefix in the string, or NULL if not found.
 */
char *custom_starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
 * custom_strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: A pointer to the destination buffer.
 */
char *custom_strcat(char *dest, char *src)
{
char *result = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (result);
}

