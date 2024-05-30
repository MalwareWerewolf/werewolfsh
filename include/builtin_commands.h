#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

int werewolfsh_num_builtins();
int werewolfsh_cd(char **args);
int werewolfsh_help();
int werewolfsh_exit();
int werewolfsh_execute(char **args);

#endif