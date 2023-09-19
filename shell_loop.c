#include "custom_shell.h"

/**
 * run_shell - Main loop for a custom shell program.
 * @info: Pointer to the shell's information struct.
 * @av: Argument vector from main.
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int run_shell(info_t *info, char **av)
{
ssize_t read_result = 0;
int builtin_ret = 0;

while (read_result != -1 && builtin_ret != -2)
{
clear_info(info);
if (is_interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
read_result = get_user_input(info);
if (read_result != -1)
{
set_info(info, av);
builtin_ret = find_builtin_command(info);
if (builtin_ret == -1)
find_and_execute_command(info);
}
else if (is_interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history_to_file(info);
free_info(info, 1);
if (!is_interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->error_code == -1)
exit(info->status);
exit(info->error_code);
}
return (builtin_ret);
}

/**
 * find_builtin_command - Find and execute a built-in command.
 * @info: Pointer to the shell's information struct.
 *
 * Return: -1 if the built-in command was not found,
 *          0 if the built-in command executed successfully,
 *          1 if the built-in command was found but not successful,
 *          2 if the built-in command signals exit().
 */
int find_builtin_command(info_t *info)
{
int i, builtin_ret = -1;
builtin_table builtintbl[] = {
{"exit", my_custom_exit},
{"env", my_custom_env},
{"help", my_custom_help},
{"history", my_custom_history},
{"setenv", my_custom_setenv},
"unsetenv", my_custom_unsetenv},
{"cd", my_custom_cd},
{"alias", my_custom_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].command; i++)
{
if (_strcmp(info->argv[0], builtintbl[i].command) == 0)
{
info->line_count++;
builtin_ret = builtintbl[i].func(info);
break;
}
}
return (builtin_ret);
}

/**
 * find_and_execute_command - Find and execute a command in the PATH.
 * @info: Pointer to the shell's information struct.
 *
 * Return: void
 */
void find_and_execute_command(info_t *info)
{
	char *path = NULL;
	int i, arg_count;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
arg_count = count_non_delim_args(info->arg);
if (!arg_count)
return;

path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_and_execute_command(info);
}
else
{
if ((is_interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_valid_command(info, info->argv[0]))
fork_and_execute_command(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error_message(info, "Command not found\n");
}
}
}

/**
 * fork_and_execute_command - Fork and execute a command.
 * @info: Pointer to the shell's information struct.
 *
 * Return: void
 */
void fork_and_execute_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Fork Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environment_variables(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error_message(info, "Permission denied\n");
}
}
}
