#include "shell.h"
#include <string.h>

/**
 * str_tokens - Tokenizes the input string into individual tokens.
 * @str: The string to be tokenized.
 *
 * This function tokenizes the input string 'str' using
 * the "strtok" function, with delimiters " \n".
 * It returns an array of pointers to individual tokens.
 * The returned array is null pointer-terminated.
 * It's also allocated dynamically using malloc,
 * and must be freed by the caller.
 * If the malloc call fails or if 'str' is NULL,
 * str_tokens returns NULL.
 *
 * Return: NULL-terminated array of pointers to tokens in the 'str' string
 * if the malloc call was successful, NULL otherwise.
 */
char **str_tokens(char *str)
{
	char **result;
	char *token;
	int result_index = 0;

	if (!str)
		return (NULL);

	result = malloc(sizeof(char *) * (strlen(str) + 1));
	if (!result)
		return (NULL);

	while ((token = strsep(&str, " \n")) != NULL)
	{
		result[result_index++] = token;
	}

	result[result_index] = NULL;

	return (result);
}
