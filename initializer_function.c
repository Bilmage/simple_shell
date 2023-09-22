#include "shell.h"

/**
 * initializer - Function that initiates command execution
 * @current_command: The current command to execute
 * @type_command: The type of command (external or path)
 *
 * This function is responsible for launching external or path-based commands
 * in a child process and waiting for their completion in the parent process.
 *
 * Return: Void function
 */

void initializer(char **current_command, int type_command)
{
pid_t PID;

if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
{
PID = fork();
if (PID == 0)
execute_command(current_command, type_command);
else
{
waitpid(PID, &status, 0);
status >>= 8;
}
}
else
execute_command(current_command, type_command);
}
