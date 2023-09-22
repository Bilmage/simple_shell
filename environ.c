#include "shell.h"

/**
 * _myenv - Display the current environment variables.
 * @info: Pointer to a structure containing potential arguments.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
 * _getenv - Get the value of an environment variable by name.
 * @info: Pointer to a structure containing potential arguments.
 * @name: Name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * _mysetenv - Set or modify an environment variable.
 * @info: Pointer to a structure containing potential arguments.
 * Return: 0 if successful, 1 if an error occurred.
 */
int _mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Usage: _mysetenv VARIABLE VALUE\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Pointer to a structure containing potential arguments.
 * Return: 0 if successful, 1 if an error occurred.
 */
int _myunsetenv(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Usage: _myunsetenv VARIABLE [VARIABLE ...]\n");
return (1);
}
for (i = 1; i < info->argc; i++)
_unsetenv(info, info->argv[i]);

return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Pointer to a structure containing potential arguments.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}