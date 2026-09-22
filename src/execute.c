
#include "shell.h"

void execute_command(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("minishell: fork failed");
        return;
    }

    if (pid == 0) {
        // Child process: execute the requested command.
        execvp(args[0], args);

        // This line runs only if execvp fails.
        perror("minishell: command execution failed");
        _exit(127);
    }

    // Parent process: wait for the child to finish.
    int status;

    while (waitpid(pid, &status, 0) < 0) {
        if (errno == EINTR) {
            continue;
        }

        perror("minishell: waitpid failed");
        break;
    }
}