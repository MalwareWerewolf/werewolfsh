#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>

#define WEREWOLFSH_RL_BUFSIZE 1024

#define WEREWOLFSH_TOK_BUFSIZE 64
#define WEREWOLFSH_TOK_DELIM " \t\r\n\a"

char *werewolfsh_read_line(void);
char **werewolfsh_split_line(char *line);

#endif
