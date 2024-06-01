#include "builtin_commands.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <unistd.h> // POSIX system APIs
#include <sys/syslimits.h>
#include <sys/wait.h> // Wait for child processes to exit

char* builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[])(char***) = {
	&werewolfsh_cd,
	&werewolfsh_help,
	&werewolfsh_exit
};

int werewolfsh_num_builtins(void)
{
	return sizeof(builtin_str) / sizeof(char*);
}

int werewolfsh_cd(char*** args)
{
	uid_t uid = getuid();
	struct passwd* pw = getpwuid(uid);
	if (!pw) {
		perror("Retreive Home Dir");
		return 0;
	}
	if (args[0][1] == NULL) {
		if (chdir(pw->pw_dir) != 0) {
			perror("sh: cd");
		}
	} else {
		char path[PATH_MAX];
		char expanded_path[PATH_MAX];
		char* tilda = strchr(args[0][1], '~');
		if (tilda) {
			strcpy(path, pw->pw_dir);
			strcat(path, tilda + 1);
		} else {
			strcpy(path, args[0][1]);
		}
		char* exp_path = realpath(path, expanded_path);
		if (!exp_path) {
			perror("realpath");
			return 0;
		}
		if (chdir(exp_path) != 0) {
			perror("werewolfsh: cd");
		}
	}

	return 1;
}

int werewolfsh_help(void)
{
	int i;
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < werewolfsh_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int werewolfsh_exit(void) { return 0; }

void execute_command(char** args, int input_fd, int output_fd)
{
	// Create child
	pid_t pid;
	int status;

	if ((pid = fork()) == 0) {
		// Child Process context

		// Redirect in and out file descriptors if needed
		if (input_fd != STDIN_FILENO) {
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}

		if (output_fd != STDOUT_FILENO) {
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}

		// Execute command
		if (execvp(args[0], args) == -1) {
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0) {
		// Fork failed
		perror("fork");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

int execute_pipeline(char*** commands, int num_commands)
{
	// No command given
	if (commands[0][0][0] == '\0') {
		return 1;
	}

	// Create pipes
	int** pipes = malloc((num_commands - 1) * sizeof(int*));
	for (int i = 0; i < num_commands - 1; i++) {
		pipes[i] = malloc(2 * sizeof(int)); // pipes[i][0] = in, pipes[i][1] = out
		if (pipe(pipes[i]) == -1) {
			perror("pipe");
			return 0;
		}
	}

	// Execute commands in the pipeline
	for (int i = 0; i < num_commands - 1; i++) {

		int input_fd = (i == 0) ? STDIN_FILENO : pipes[i - 1][0];
		int output_fd = pipes[i][1];

		execute_command(commands[i], input_fd, output_fd);
		close(output_fd); // We are done writing to this pipe
	}

	// Execute last (or only) command
	int input_fd = (num_commands > 1) ? pipes[num_commands - 2][0] : STDIN_FILENO;
	int output_fd = STDOUT_FILENO;
	execute_command(commands[num_commands - 1], input_fd, output_fd);

	// Close/Cleanup pipes
	for (int i = 0; i < num_commands - 1; i++) {
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
	return 1;
}

int werewolfsh_run(char*** commands, int num_commands)
{
	if (commands[0][0] == NULL) {
		// No command given
		return 1;
	}

	// Check shell builtins
	for (int i = 0; i < werewolfsh_num_builtins(); i++) {
		if (strcmp(commands[0][0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(commands);
		}
	}

	return execute_pipeline(commands, num_commands);
}
