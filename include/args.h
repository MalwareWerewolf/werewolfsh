#ifndef ARGS_h
#define ARGS_h

char **werewolfsh_split_pipes(char *line);
char ***werewolfsh_split_args(char **commands, int *status);

#endif
