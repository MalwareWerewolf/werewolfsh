#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

int werewolfsh_num_builtins();
int werewolfsh_cd(char ***args);
int werewolfsh_help();
int werewolfsh_exit();
int execute_pipeline(char ***commands, int num_commands);
void execute_command(char **args, int input_fd, int output_fd);
int werewolfsh_run(char ***commands, int num_commands);

#endif
