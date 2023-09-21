#include "shell.h"

/**
 * _print_string - displays a provided string
 * @str: the string to be displayed
 *
 * Return: None
 */
void _print_string(char *str)
{
int index = 0;

if (!str)
return;

while (str[index] != '\0')
{
_print_character(str[index]);
index++;
}
}

/**
 * _print_character - writes the character 'c' to the standard error stream
 * @c: The character to be printed
 *
 * Return: On success, it returns 1.
 * On error, -1 is returned, and the error code is set appropriately.
 */
int _print_character(char c)
{
static int buffer_index;
static char buffer[WRITE_BUFFER_SIZE];

if (c == FLUSH_BUFFER || buffer_index >= WRITE_BUFFER_SIZE)
{
write(2, buffer, buffer_index);
buffer_index = 0;
}

if (c != FLUSH_BUFFER)
buffer[buffer_index++] = c;

return (1);
}

/**
 * _write_to_fd - writes the character 'c' to the specified file descriptor
 * @c: The character to be printed
 * @fd: The file descriptor to write to
 *
 * Return: On success, it returns 1.
 * On error, -1 is returned, and the error code is set appropriately.
 */
int _write_to_fd(char c, int fd)
{
static int buffer_index;
static char buffer[WRITE_BUFFER_SIZE];

if (c == FLUSH_BUFFER || buffer_index >= WRITE_BUFFER_SIZE)
{
write(fd, buffer, buffer_index);
buffer_index = 0;
}

if (c != FLUSH_BUFFER)
buffer[buffer_index++] = c;

return (1);
}

/**
 * _display_string_to_fd - displays a provided string to a specified file descriptor
 * @str: the string to be displayed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _display_string_to_fd(char *str, int fd)
{
int chars_written = 0;

if (!str)
return (0);

while (*str)
{
chars_written += _write_to_fd(*str++, fd);
}

return (chars_written);
}

