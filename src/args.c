#include "args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char **werewolfsh_split_pipes(char *line){
    int position = 0;
    char **tokens = calloc(16, sizeof(char*));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "werewolfsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, "|");
    
    while (token != NULL)
    {
        tokens[position++] = token;
        token = strtok(NULL, "|");
    }
    
    for (int i = 0; i < position; i++) {
        // Trim leading whitespace
        while (*tokens[i] == ' ' || *tokens[i] == '\n') {
            tokens[i]++;
        }
        // Trim trailing whitespace
        if (*tokens[i] != '\0') { // Only proceed if the string is not empty
            char *end_of_str = strrchr(tokens[i], '\0');
            --end_of_str;
            while (end_of_str >= tokens[i] && (*end_of_str == ' ' || *end_of_str == '\n')) {
                *end_of_str = '\0';
                --end_of_str;
            }
        }
    }
    
    return tokens;
}

char ***werewolfsh_split_args(char **commands, int *status) {
  int outer_pos = 0;
  char ***command_args = calloc(16, sizeof(char**));
  if (!command_args) {
    perror("calloc failed");
    exit(1);
  }

  for (int i = 0; commands[i]; i++) {
    int pos = 0;
    char **args = calloc(16, sizeof(char*));
    if (!args) {
      perror("calloc failed");
      exit(1);
    }

    bool inside_string = false;
    char *current_token = &commands[i][0];

    for (int j = 0; commands[i][j]; j++) {
      if (commands[i][j] == '"' && !inside_string) {
        // Beginning of a string
        commands[i][j++] = '\0';
        if (commands[i][j] != '"') {
          inside_string = true;
          current_token = &commands[i][j];
        } else {
          commands[i][j] = '\0';
          current_token = &commands[i][++j];
        }
      } else if (inside_string) {
        if (commands[i][j] == '"') {
          // Ending of a string
          inside_string = false;
          commands[i][j] = '\0';
          args[pos++] = current_token;
          current_token = NULL;
        } else {
          // Character in string
          continue;
        }
      } else if (commands[i][j] == ' ') {
        // Space delimeter
        if (current_token && *current_token != ' ') {
          args[pos++] = current_token;
        }
        current_token = &commands[i][j+1]; // Go past the space
        commands[i][j] = '\0';
      } else if (commands[i][j] == '$' && commands[i][j+1] && commands[i][j+1] != ' ') {
        // Environment variable
        args[pos++] = getenv(&commands[i][++j]);
        while (commands[i][j]) {
          ++j;
        }
        current_token = &commands[i][j+1];
      } else {
        // Regular character
        continue;
      }
    }

    // Check if string literal was finished
    if (inside_string) {
      *status = -1;
      return command_args;
    } else if (current_token && *current_token != ' ') {
      // Add last argument to the array
      args[pos++] = current_token;
    }

    // Add this commands arguments array to the outer array
    command_args[outer_pos++] = args;
  }

  *status = outer_pos;
  return command_args;
}
