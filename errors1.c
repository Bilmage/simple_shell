#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: The integer value if successful, -1 on error
 */
int str_to_int(char *s)
{
int i = 0;
long int result = 0;

if (*s == '+')
s++;
for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return ((int) result);
}

/**
 * print_error_message - prints an error message
 * @info: the parameter & return info struct
 * @error_msg: string containing specified error message
 */
void print_error_message(info_t *info, char *error_msg)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(error_msg);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @input: the input integer
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
int (*output_char)(char) = _putchar;
int i, count = 0;
unsigned int abs_value, current;

if (fd == STDERR_FILENO)
output_char = _eputchar;

if (input < 0)
{
abs_value = -input;
output_char('-');
count++;
}
else
{
abs_value = input;
}

current = abs_value;
for (i = 1000000000; i > 1; i /= 10)
{
if (abs_value / i)
{
output_char('0' + current / i);
count++;
}
current %= i;
}
output_char('0' + current);
count++;

return (count);
}

/**
 * num_to_str - converts a number to a string
 * @num: the number to convert
 * @base: the base for conversion
 * @flags: argument flags
 *
 * Return: a string representation of the number
 */
char *num_to_str(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}

array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * remove_comment - replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void remove_comment(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
{
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
}
