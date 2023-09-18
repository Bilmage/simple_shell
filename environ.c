#include "shell.h"

/**
 * _print_environment - Print the current environment variables.
 * @info: Pointer to a structure containing potential arguments.
 *
 * This function prints the list of environment variables.
 */
int _print_environment(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
 * _get_environment_variable - Get the value of an environment variable.
 * @info: Pointer to a structure containing potential arguments.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: The value of the specified environment variable, or NULL if not found.
 */
char *_get_environment_variable(info_t *info, const char *name)
{
list_t *node = info->env;
char *value;

while (node)
{
value = starts_with(node->str, name);
if (value && *value)
return (value);
node = node->next;
}
return (NULL);
}

/**
 * _set_environment_variable - Initialize a new environment variable or modify an existing one.
 * @info: Pointer to a structure containing potential arguments.
 *
 * This function sets or modifies an environment variable with the specified name and value.
 *
 * Return: Always 0.
 */
int _set_environment_variable(info_t *info)
{
if (info->argc != 3)
{
_eputs("Usage: setenv <name> <value>\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * _unset_environment_variable - Remove an environment variable.
 * @info: Pointer to a structure containing potential arguments.
 *
 * This function removes one or more environment variables.
 *
 * Return: Always 0.
 */
int _unset_environment_variable(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Usage: unsetenv <name1> [<name2> ...]\n");
return (1);
}
for (i = 1; i < info->argc; i++)
_unsetenv(info, info->argv[i]);

return (0);
}

/**
 * populate_environment_list - Populate the environment linked list.
 * @info: Pointer to a structure containing potential arguments.
 *
 * This function populates the linked list with environment variables.
 *
 * Return: Always 0.
 */
int populate_environment_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
