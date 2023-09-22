#include "shell.h"

/**
 * Function: tokenizeString
 * Description: Tokenizes the input string and stores tokens in an array.
 * @input_string: The input to be parsed.
 * @delim: The delimiter to be used (a single-character string).
 *
 * Return: An array of tokens.
 */
char **tokenizeString(char *input_string, char *delim)
{
int num_delim = 0;
char **tokens = NULL;
char *token = NULL;
char *save_ptr = NULL;

token = customStrtok(input_string, delim, &save_ptr);

while (token != NULL)
{
tokens = customRealloc(tokens, sizeof(*tokens) * num_delim, sizeof(*tokens) * (num_delim + 1));
tokens[num_delim] = token;
token = customStrtok(NULL, delim, &save_ptr);
num_delim++;
}

tokens = customRealloc(tokens, sizeof(*tokens) * num_delim, sizeof(*tokens) * (num_delim + 1));
tokens[num_delim] = NULL;

return (tokens);
}

/**
 * Function: customPrint
 * Description: Prints a string to the specified stream.
 * @string: The string to be printed.
 * @stream: The stream to print to.
 *
 * Return: None.
 */
void customPrint(char *string, int stream)
{
int i = 0;

for (; string[i] != '\0'; i++)
writeToStream(stream, &string[i], 1);
}

/**
 * Function: removeNewline
 * Description: Removes newline characters from a string.
 * @str: The string to process.
 *
 * Return: None.
 */
void removeNewline(char *str)
{
int i = 0;

while (str[i] != '\0')
{
if (str[i] == '\n')
break;
i++;
}
str[i] = '\0';
}

/**
 * Function: customStrcpy
 * Description: Copies a string from source to destination.
 * @source: The source string.
 * @dest: The destination string.
 *
 * Return: None.
 */
void customStrcpy(char *source, char *dest)
{
int i = 0;

for (; source[i] != '\0'; i++)
dest[i] = source[i];
dest[i] = '\0';
}

/**
 * Function: customStrlen
 * Description: Counts the length of a string.
 * @string: The string to measure.
 *
 * Return: The length of the string.
 */
int customStrlen(char *string)
{
int len = 0;

if (string == NULL)
return (len);
for (; string[len] != '\0'; len++)
;
return (len);
}

