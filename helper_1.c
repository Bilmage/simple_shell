#include "shell.h"

/**
 * Function: compareStrings
 * Description: Compares two strings and returns their difference.
 * @first: The first string to be compared.
 * @second: The second string to be compared.
 *
 * Return: The difference between the two strings.
 */
int compareStrings(char *first, char *second)
{
int i = 0;

while (first[i] != '\0')
{
if (first[i] != second[i])
break;
i++;
}
return (first[i] - second[i]);
}

/**
 * Function: concatenateStrings
 * Description: Concatenates two strings and returns the address of the new string.
 * @destination: The string to which the other string will be concatenated.
 * @source: The string to concatenate.
 *
 * Return: The address of the new string.
 */
char *concatenateStrings(char *destination, char *source)
{
char *newString =  NULL;
int lenDest = stringLength(destination);
int lenSource = stringLength(source);

newString = allocateMemory(sizeof(*newString) * (lenDest + lenSource + 1));
copyString(destination, newString);
copyString(source, newString + lenDest);
newString[lenDest + lenSource] = '\0';
return (newString);
}

/**
 * Function: prefixLength
 * Description: Gets the length of a prefix substring in str1 that is part of str2.
 * @str1: The string to be searched.
 * @str2: The string to use for comparison.
 *
 * Return: The number of bytes in the initial segment of str1 that are part of str2.
 */
int prefixLength(char *str1, char *str2)
{
int i = 0;
int match = 0;

while (str1[i] != '\0')
{
if (findCharacter(str2, str1[i]) == NULL)
break;
match++;
i++;
}
return (match);
}

/**
 * Function: segmentIndex
 * Description: Computes the segment of str1 consisting of characters not in str2
 *              and returns the index at which a character in str1 exists in str2.
 * @str1: The string to be searched.
 * @str2: The string to use for comparison.
 *
 * Return: The index at which a character in str1 exists in str2.
 */
int segmentIndex(char *str1, char *str2)
{
int len = 0, i;

for (i = 0; str1[i] != '\0'; i++)
{
if (findCharacter(str2, str1[i]) != NULL)
break;
len++;
}
return (len);
}

/**
 * Function: findCharacter
 * Description: Locates a character in a string and returns a pointer to its first occurrence.
 * @s: The string to be searched.
 * @c: The character to be checked.
 *
 * Return: A pointer to the first occurrence of c in s.
 */
char *findCharacter(char *s, char c)
{
int i = 0;

for (; s[i] != c && s[i] != '\0'; i++)
;
if (s[i] == c)
return (s + i);
else
return (NULL);
}

