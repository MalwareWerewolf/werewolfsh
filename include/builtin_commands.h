#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

int lsh_num_builtins();
int lsh_cd(char **args);
int lsh_help();
int lsh_exit();
int lsh_execute(char **args);

#endif