#include "shell.h"

/**
 * obtain_history_file_path - Retrieves the path to the history file
 * @info: A structure containing relevant parameters
 *
 * Return: A dynamically allocated string containing the path to the history file
 */
char *obtain_history_file_path(info_t *info)
{
char *home_directory, *file_path;

home_directory = _getenv(info, "HOME=");
if (!home_directory)
return (NULL);

file_path = malloc(sizeof(char) * (_strlen(home_directory) + _strlen(HISTORY_FILE) + 2));
if (!file_path)
return (NULL);

file_path[0] = 0;
_strcpy(file_path, home_directory);
_strcat(file_path, "/");
_strcat(file_path, HISTORY_FILE);

return (file_path);
}

/**
 * write_history_to_file - Creates a new file or appends to an existing one for history storage
 * @info: A structure containing relevant parameters
 *
 * Return: 1 on success, -1 on failure
 */
int write_history_to_file(info_t *info)
{
ssize_t file_descriptor;
char *file_name = obtain_history_file_path(info);
list_t *node = NULL;

if (!file_name)
return (-1);

file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);

if (file_descriptor == -1)
return (-1);

for (node = info->history; node; node = node->next)
{
_puts_to_fd(node->str, file_descriptor);
_put_to_fd('\n', file_descriptor);
}

_put_to_fd(FLUSH_BUFFER, file_descriptor);
close(file_descriptor);

return (1);
}

/**
 * read_history_from_file - Reads history entries from a file
 * @info: A structure containing relevant parameters
 *
 * Return: The number of history entries read, or 0 on failure
 */
int read_history_from_file(info_t *info)
{
int i, last = 0, entry_count = 0;
ssize_t file_descriptor, read_length, file_size = 0;
struct stat file_stat;
char *buffer = NULL, *file_name = obtain_history_file_path(info);

if (!file_name)
return (0);

file_descriptor = open(file_name, O_RDONLY);
free(file_name);

if (file_descriptor == -1)
return (0);

if (!fstat(file_descriptor, &file_stat))
file_size = file_stat.st_size;

if (file_size < 2)
return (0);

buffer = malloc(sizeof(char) * (file_size + 1));
if (!buffer)
return (0);

read_length = read(file_descriptor, buffer, file_size);
buffer[file_size] = 0;

if (read_length <= 0)
return (free(buffer), 0);

close(file_descriptor);

for (i = 0; i < file_size; i++)
{
if (buffer[i] == '\n')
{
buffer[i] = 0;
add_to_history_list(info, buffer + last, entry_count++);
last = i + 1;
}
}

if (last != i)
add_to_history_list(info, buffer + last, entry_count++);

free(buffer);
info->histcount = entry_count;

while (info->histcount-- >= MAX_HISTORY_ENTRIES)
delete_node_at_index(&(info->history), 0);

renumber_history_entries(info);

return (info->histcount);
}

/**
 * add_to_history_list - Appends a history entry to the linked list
 * @info: A structure containing potential arguments
 * @buf: A buffer containing the history entry
 * @entry_count: The current history entry count
 *
 * Return: Always 0
 */
int add_to_history_list(info_t *info, char *buf, int entry_count)
{
list_t *node = NULL;

if (info->history)
node = info->history;

add_node_end(&node, buf, entry_count);

if (!info->history)
info->history = node;

return (0);
}

/**
 * renumber_history_entries - Renumbers the history entries in the linked list after changes
 * @info: A structure containing potential arguments
 *
 * Return: The new history entry count
 */
int renumber_history_entries(info_t *info)
{
list_t *node = info->history;
int count = 0;

while (node)
{
node->num = count++;
node = node->next;
}

return (info->histcount = count);
}

