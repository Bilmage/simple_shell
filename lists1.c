#include "shell.h"

/**
 * list_length - Determine the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_length(const list_t *h)
{
size_t count = 0;

while (h)
{
h = h->next;
count++;
}
return (count);
}

/**
 * list_to_strings - Convert a linked list of strings to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t list_size = list_length(head);
char **str_array;
char *str;

if (!head || !list_size)
return (NULL);

str_array = malloc(sizeof(char *) * (list_size + 1));
if (!str_array)
return (NULL);

for (size_t i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (size_t j = 0; j < i; j++)
free(str_array[j]);
free(str_array);
return (NULL);
}

str = _strcpy(str, node->str);
str_array[i] = str;
}

str_array[list_size] = NULL;
return (str_array);
}

/**
 * print_list - Print all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *h)
{
size_t count = 0;

while (h)
{
_puts(convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
count++;
}
return (count);
}

/**
 * node_starts_with - Find a node whose string starts with a given prefix.
 * @node: Pointer to the list head.
 * @prefix: The prefix to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * get_node_index - Get the index of a node in the list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node to find.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
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

