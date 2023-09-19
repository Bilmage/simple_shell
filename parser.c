/**
 * is_executable - checks if a file is an executable command
 * @info: pointer to info struct
 * @path: path to the file
 *
 * Return: 1 if it's executable, 0 otherwise
 */
int is_executable(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * duplicate_chars - duplicates characters in a string
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer containing the duplicated characters
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buffer[k++] = pathstr[i];
buffer[k] = 0;
return (buffer);
}

/**
 * find_command_in_path - finds a command in the PATH string
 * @info: pointer to info struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: the full path of the command if found, or NULL
 */
char *find_command_in_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = duplicate_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
	_strcat(path, "/");
	_strcat(path, cmd);
}
if (is_executable(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
