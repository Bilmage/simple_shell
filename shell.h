#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* These are the read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command for chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_numbers() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr – for singly linked list
 * @num: this is the number field
 * @str: for a string
 * @next: this points to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 * struct passinfo – This contains pseudo-arguments to pass into a function,
 * For allowing uniform prototype for function pointer struct
 * @arg: This is a string generated from getline containing arguements
 * @argv:This is an array of strings generated from arg
 * @path: This is a string path for the current command
 * @argc: For argument count
 * @line_count: error count
 * @err_num: This is the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: for program filename
 * @env: This is linked list local copy of environ
 * @environ: This is a custom modified copy of environ from LL
 * @history: for the history node
 * @alias: for the alias node
 * @env_changed: For only if environ was changed
 * @status: This is the return status of the last exec'd command
 * @cmd_buf: An address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: This is a CMD_type ||, &&, ;
 * @readfd: This is the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* This is a pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* A CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \0, 0, 0}

/**
 * struct builtin – This contains a builtin string and related function
 * @type: This is the builtin command flag
 * @func: This is the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* For shloop.c */
int run_shell(info_t *info, char **av);
int find_builtin_command(info_t *info);
void find_and_execute_command(info_t *info);
void fork_and_execute_command(info_t *info);

/* For parser.c */
int is_executable(info_t *info, char *path);
char *duplicate_chars(char *pathstr, int start, int stop);
char *find_command_in_path(info_t *info, char *pathstr, char *cmd);

/* For loophsh.c */
int loophsh(char **);

/* For errors.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* For string.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* For string1.c */
char *custom_copy_string(char *dest, const char *src);
char *custom_duplicate_string(const char *str);
void custom_print_string(const char *str);
int custom_print_character(char c);

/* For exits.c */
char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strncat(char *dest, const char *src, size_t n);
char *my_strchr(const char *s, int c);

/* For tokenizer.c */
char **strtow(char *str, char *delim);
char **strtow2(char *str, char d);

/* For realloc.c */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* For memory.c */
int freeAndNull(void **ptr);

/* For atoi.c */
int check_interactive_mode(info_t *info);
int is_delimiter(char c, char *delim);
int is_alpha_character(int c);
int string_to_integer(char *s);

/* For errors1.c */
int str_to_int(char *s);
void print_error_message(info_t *info, char *error_msg);
int print_decimal(int input, int fd);
char *num_to_str(long int num, int base, int flags);
void remove_comment(char *buf);

/* For builtin.c */
int my_exit(info_t *info);
int my_cd(info_t *info);
int my_help(info_t *info);

/* For builtin1.c */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
set_alias(info_t *info, char *str);

/*For getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* For getinfo.c */
void clearInfo(info_t *info);
void setInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);

/* For environ.c */
char *_get_environment_variable(info_t *info, const char *name);
int _print_environment(info_t *info)
int _set_environment_variable(info_t *info);
int _unset_environment_variable(info_t *info);
int populate_environment_list(info_t *info);

/* For getenv.c */
char **convertEnvironmentToList(info_t *info);
int unsetEnvironmentVariable(info_t *info, char *var);
int setEnvironmentVariable(info_t *info, char *var, char *value);

/* For history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* For lists.c */
list_t *addNodeToFront(list_t **head, const char *str, int num);
list_t *addNodeToEnd(list_t **head, const char *str, int num);
size_t printListStrings(const list_t *h);
int deleteNodeAtIndex(list_t **head, unsigned int index);
void freeListNodes(list_t **headPtr);

/* For lists1.c */
size_t list_length(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* For vars.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

#endif
