#include "line.h"
#include "builtin_commands.h"
#include <stdlib.h>
#include <stdio.h>

void welcomeScreen()
{
    printf("\n-------------------------------------------------\n");
    printf("\tWelcome to shell version \n");
    puts("\tAuthor: MalwareWerewolf");
    printf("-------------------------------------------------\n");
    printf("\n\n");
}

int main()
{
    char *line;
    char **args;
    int status;

    welcomeScreen();

    do
    {
        printf("> ");
        line = werewolfsh_read_line();
        args = werewolfsh_split_line(line);
        status = werewolfsh_execute(args);

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
