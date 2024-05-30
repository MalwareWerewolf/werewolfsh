#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>

#define LSH_RL_BUFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char *lsh_read_line(void);
char **lsh_split_line(char *line);

#endif
