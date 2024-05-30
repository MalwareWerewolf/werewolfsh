#include "line.h"
#include "builtin_commands.h"
#include <stdlib.h>
#include <stdio.h>

void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);
        
        free(line);
        free(args);
    } while (status);
}

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
    welcomeScreen();
    lsh_loop();

    return EXIT_SUCCESS;
}
