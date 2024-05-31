#include "line.h"
#include "builtin_commands.h"
#include "args.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void welcomeScreen()
{
    printf("\n-------------------------------------------------\n");
    printf("\tWelcome to werewolfsh \n");
    puts("\tAuthor: MalwareWerewolf");
    printf("-------------------------------------------------\n");
    printf("\n\n");
}

int main() {
  int status = 0;
  welcomeScreen();
    
  while (1) {
    // Prompt
    // char *cwd = getcwd(NULL, 0);
    // printf("%s => ", cwd);

    printf("> ");

    char *line = werewolfsh_read_line();
    char **commands = werewolfsh_split_pipes(line);
    char ***args = werewolfsh_split_args(commands, &status);
    if (status == -1) {
      fprintf(stderr, "shell: Expected end of quoted string\n");
    } else if (werewolfsh_run(args, status) == 0) {
      exit(EXIT_SUCCESS);
    }

    for (int i = 0; args[i]; i++) {
      free(args[i]);
    }
    free(args);
    free(commands);
    free(line);
    //free(cwd);
  }
}
