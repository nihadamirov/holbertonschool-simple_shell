#include "shell.h"

/**
 * str_tokens - Tokenizes a string into an array of
 * pointers to individual tokens.
 *
 * @str: The string to tokenize.
 *
 * This function tokenizes the input string 'str' using "strtok(str, " \n")".
 * The returned array is null pointer-terminated and dynamically allocated.
 * It needs to be freed by the caller.
 * If the function fails to allocate memory or if 'str' is NULL,
 * it returns NULL.
 *
 * Return: Pointer to a null pointer-terminated array of pointers to tokens
 * in the input string 'str' if the memory allocation is successful,
 * NULL otherwise.
 */
char **str_tokens(char *str)
{
    char **result;
    char *token;
    int str_len;
    int result_index = 0;

    if (!str)
        return (NULL);

    str_len = _strlen(str);

    result = malloc(sizeof(char *) * (str_len + 1));
    if (!result)
        return (NULL);

    token = strtok(str, " \n");
    while (token)
    {
        result[result_index] = token;
        result_index++;
        token = strtok(NULL, " \n");
    }
    result[result_index] = NULL;

    return (result);
}

