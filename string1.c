#include "custom_string.h"

/**
 * custom_copy_string - Copies a string from source to destination.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: A pointer to the destination buffer.
 */
char *custom_copy_string(char *dest, const char *src)
{
int index = 0;

if (dest == src || src == NULL)
return (dest);

while (src[index])
{
dest[index] = src[index];
index++;
}

dest[index] = '\0';
return (dest);
}

/**
 * custom_duplicate_string - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */
char *custom_duplicate_string(const char *str)
{
int length = 0;
char *duplicate;

if (str == NULL)
return (NULL);

while (*str++)
length++;

duplicate = malloc(sizeof(char) * (length + 1));
if (!duplicate)
return (NULL);

for (length++; length--;)
duplicate[length] = *--str;

return (duplicate);
}

/**
 * custom_print_string - Prints a string to the standard output.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void custom_print_string(const char *str)
{
int index = 0;

if (!str)
return;

while (str[index] != '\0')
{
custom_print_character(str[index]);
index++;
}
}

/**
 * custom_print_character - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_print_character(char c)
{
static int index;
static char buffer[WRITE_BUFFER_SIZE];

if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
{
write(1, buffer, index);
index = 0;
}

if (c != BUFFER_FLUSH)
buffer[index++] = c;

return (1);
}
