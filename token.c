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
	if (!str)
		return (NULL);

	int str_len = _strlen(str);
	int token_count = 0;
	int token_index = 0;
	int i;
	char **result;
	char *token;

	for (i = 0; i < str_len; i++)
	{
		if (str[i] == ' ' || str[i] == '\n')
			token_count++;
	}

	result = malloc(sizeof(char *) * (token_count + 1));
	if (!result)
		return (NULL);

	token = strtok(str, " \n");
	while (token)
	{
		result[token_index++] = token;
		token = strtok(NULL, " \n");
	}
	result[token_index] = NULL;

	return (result);
}

