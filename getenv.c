#include "shell.h"

/**
 * @brief Converts a linked list of environment variables to an array of strings.
 *
 * This function takes a linked list of environment variables and converts it
 * into an array of strings. If the environment has been modified, it recreates
 * the array to reflect the changes.
 *
 * @param info A structure containing potential arguments and environment data.
 * @return An array of strings representing the environment variables.
 */
char **convertEnvironmentToList(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = listToCharArray(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
 * @brief Unsets an environment variable by name.
 *
 * This function removes an environment variable with a specified name from the
 * linked list of environment variables.
 *
 * @param info A structure containing potential arguments and environment data.
 * @param var  The name of the environment variable to unset.
 * @return 1 if the variable was successfully deleted, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = startsWith(node->str, var);
if (p && *p == '=')
{
info->env_changed = deleteNodeAtIndex(&(info->env), i);
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
 * @brief Sets or modifies an environment variable.
 *
 * This function initializes a new environment variable or modifies an existing
 * one with the specified name and value.
 *
 * @param info  A structure containing potential arguments and environment data.
 * @param var   The name of the environment variable.
 * @param value The value to assign to the environment variable.
 * @return Always returns 0.
 */
int setEnvironmentVariable(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(strlen(var) + strlen(value) + 2);
if (!buf)
return (1);
strcpy(buf, var);
strcat(buf, "=");
strcat(buf, value);
node = info->env;
while (node)
{
p = startsWith(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
addNodeEnd(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

