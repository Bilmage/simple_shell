#include "shell.h"

/**
 * determine_list_length - Calculates the size of a linked list
 * @h: Pointer to the first node
 *
 * Return: The size of the linked list
 */
size_t determine_list_length(const list_t *h)
{
size_t size = 0;

while (h)
{
h = h->next;
size++;
}

return (size);
}

/**
 * convert_list_to_strings - Converts a linked list to an array of strings
 * @head: Pointer to the first node
 *
 * Return: An array of strings
 */
char **convert_list_to_strings(list_t *head)
{
list_t *node = head;
size_t size = determine_list_length(head);
char **str_array;
char *str;

if (!head || !size)
return (NULL);

str_array = malloc(sizeof(char *) * (size + 1));

if (!str_array)
return (NULL);

for (size = 0; node; node = node->next, size++)
{
str = malloc(_strlen(node->str) + 1);

if (!str)
{
for (size_t j = 0; j < size; j++)
free(str_array[j]);

free(str_array);
return (NULL);
}

str = _strcpy(str, node->str);
str_array[size] = str;
}

str_array[size] = NULL;
return (str_array);
}

/**
 * display_list_elements - Prints all elements of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: The size of the list
 */
size_t display_list_elements(const list_t *h)
{
size_t size = 0;

while (h)
{
_puts(display_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
size++;
}

return (size);
}

/**
 * find_node_with_prefix - Finds a node whose string starts with a given prefix
 * @node: Pointer to the list head
 * @prefix: The prefix to match
 * @c: The next character after the prefix to match
 *
 * Return: The matching node or NULL
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
char *match = NULL;

while (node)
{
match = starts_with(node->str, prefix);

if (match && ((c == -1) || (*match == c)))
return (node);

node = node->next;
}

return (NULL);
}

/**
 * obtain_node_index - Retrieves the index of a node
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: The index of the node or -1 if not found
 */
ssize_t obtain_node_index(list_t *head, list_t *node)
{
size_t index = 0;

while (head)
{
if (head == node)
return (index);

head = head->next;
index++;
}

return (-1);
}

