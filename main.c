#include "shell.h"

/**
 * main - Entry point of a custom shell program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
/* Initialize a data structure for shell information */
info_t info[] = { INFO_INIT };
int fd = 2;

/* Perform a custom assembly operation on 'fd' */
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));

/* Check if there is exactly one command-line argument */
if (ac == 2)
{
/* Attempt to open the specified file for reading */
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
/* Handle file open errors */
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
/* Print an error message and exit */
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fd;
}

/* Populate the environment variable list */
populate_env_list(info);

/* Read command history, if available */
read_history(info);

/* Start the custom shell process */
hsh(info, av);

return (EXIT_SUCCESS);
}
