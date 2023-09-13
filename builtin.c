#include "shell.h"

/**
 * my_exit - Exit the shell with a given exit status.
 *
 * @info: Structure containing potential arguments and shell information.
 *
 * Return: 0 if successful, 1 on error.
 */
int my_exit(info_t *info)
{
int exit_code;

if (info->argv[1])
{
exit_code = _erratoi(info->argv[1]);
if (exit_code == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = exit_code;
return (-2);
}

info->err_num = -1;
return (-2);
}

/**
 * my_cd - Change the current directory of the process.
 *
 * @info: Structure containing potential arguments and shell information.
 *
 * Return: Always 0.
 */
int my_cd(info_t *info)
{
char *current_dir, *target_dir, buffer[1024];
int chdir_ret;

current_dir = getcwd(buffer, 1024);
if (!current_dir)
_puts("Error: Unable to retrieve the current directory.\n");

if (!info->argv[1])
{
target_dir = _getenv(info, "HOME=");
if (!target_dir)
chdir_ret = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
else
chdir_ret = chdir(target_dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD="));
_putchar('\n');
target_dir = _getenv(info, "OLDPWD=");
chdir_ret = chdir(target_dir ? target_dir : "/");
}
else
{
target_dir = info->argv[1];
chdir_ret = chdir(target_dir);
}
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(target_dir);
_eputchar('\n');
}
else
{
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));
}

return (0);
}

/**
 * my_help - Display help information for the shell.
 *
 * @info: Structure containing potential arguments and shell information.
 *
 * Return: Always 0.
 */
int my_help(info_t *info)
{
	char **arg_array;

arg_array = info->argv;
_puts("Help: This function is not yet implemented.\n");
if (0)
{
	_puts(*arg_array);
}
return (0);
}
