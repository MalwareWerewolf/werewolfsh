#include "builtin_commands.h"
#include "process.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &werewolfsh_cd,
    &werewolfsh_help,
    &werewolfsh_exit
};

int werewolfsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int werewolfsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        chdir(getenv("HOME"));
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("werewolfsh");
        }
    }
    return 1;
}

int werewolfsh_help()
{
    int i;
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < werewolfsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int werewolfsh_exit()
{
    return 0;
}

int werewolfsh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < werewolfsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return werewolfsh_launch(args);
}