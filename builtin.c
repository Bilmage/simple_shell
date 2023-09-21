#include "shell.h"

/**
 * _myexit - Exit the shell with a specified exit status.
 * @info: Pointer to a structure containing potential arguments.
 * Return: 0 if successful, 1 if an error occurred.
 */
int _myexit(info_t *info)
{
int exit_status;

if (info->argv[1])
{
exit_status = _erratoi(info->argv[1]);
if (exit_status == -1)
{
info->status = 2;
print_error(info, "Invalid exit status: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = exit_status;
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
 * _mycd - Change the current directory of the process.
 * @info: Pointer to a structure containing potential arguments.
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("Error: Unable to get current directory\n");

if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD="));
_putchar('\n');
chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);

if (chdir_ret == -1)
{
print_error(info, "Error: Unable to change directory to ");
_eputs(info->argv[1]);
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
 * _myhelp - Display a help message.
 * @info: Pointer to a structure containing potential arguments.
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("Help: This function is not yet implemented\n");

if (0)
_puts(*arg_array);

return (0);
}
