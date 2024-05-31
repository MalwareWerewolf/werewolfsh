#include "line.h"
#include <string.h>
#include <stdbool.h>

char *werewolfsh_read_line()
{
    int bufsize = WEREWOLFSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "werewolfsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        // Read a character       
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize)
        {
            bufsize += WEREWOLFSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "werewolfsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **werewolfsh_split_line(char *line)
{
    int bufsize = WEREWOLFSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "werewolfsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, WEREWOLFSH_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += WEREWOLFSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "werewolfsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, WEREWOLFSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
