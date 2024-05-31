#ifndef LINE_H
#define LINE_H

#define WEREWOLFSH_RL_BUFSIZE 1024

#define WEREWOLFSH_TOK_BUFSIZE 64
#define WEREWOLFSH_TOK_DELIM " \t\r\n\a"

char *werewolfsh_read_line();
char **werewolfsh_split_line(char *line);

#endif
