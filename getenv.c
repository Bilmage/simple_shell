#include "shell.h"

/**
 * get_environment_copy - Returns a copy of the environment variables as a string array
 * @info: A structure holding possible function arguments, maintaining a consistent function prototype
 * Return: A pointer to the copied environment variables
 */
char **get_environment_copy(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
 * unset_environment_variable - Removes an environment variable
 * @info: A structure holding potential function arguments, maintaining a constant function prototype
 * @var: The name of the environment variable to be removed
 * Return: 1 on successful removal, 0 otherwise
 */
int unset_environment_variable(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
 * set_environment_variable - Initializes a new environment variable or modifies an existing one
 * @info: A structure holding potential function arguments, maintaining a constant function prototype
 * @var: The name of the environment variable
 * @value: The value to set for the environment variable
 * Return: Always returns 0
 */
int set_environment_variable(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = info->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

