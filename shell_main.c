#include "shell.h"

char **commands = NULL;
char *line = NULL;
char *shell_name = NULL;
int status = 0;

/**
 * main - The main function for the shell
 * @argc: Number of arguments passed to the program
 * @argv: Array of program arguments
 *
 * This function implements the shell's main loop, processes user input,
 * and executes commands. It also handles signals and errors gracefully.
 *
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
char **current_command = NULL;
int i, type_command = 0;
size_t n = 0;

signal(SIGINT, ctrl_c_handler);

shell_name = argv[0];

while (1)
{
non_interactive();

print(" ($) ", STDOUT_FILENO);

if (getline(&line, &n, stdin) == -1)
{
free(line);
exit(status);
}

remove_newline(line);
remove_comment(line);
commands = tokenizer(line, ";");

for (i = 0; commands[i] != NULL; i++)
{
current_command = tokenizer(commands[i], " ");
if (current_command[0] == NULL)
{
free(current_command);
break;
}

type_command = parse_command(current_command[0]);

initializer(current_command, type_command);
free(current_command);
}
free(commands);
}
free(line);

return (status);
}
