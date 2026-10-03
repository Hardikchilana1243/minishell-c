#include "shell.h"

void execute_pipe(char **args) {
    int pipe_position = -1;

    // Find |
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_position = i;
            break;
        }
    }

    if (pipe_position == -1) {
        return;
    }

    // Check invalid pipe syntax
    if (pipe_position == 0 || args[pipe_position + 1] == NULL) {
        fprintf(stderr, "minishell: invalid pipe syntax\n");
        return;
    }

    // Replace | with NULL.
    // This splits args into two commands.
    args[pipe_position] = NULL;

    char **left_command = args;
    char **right_command = &args[pipe_position + 1];

    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("minishell: pipe failed");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("minishell: fork failed");
        return;
    }

    if (pid1 == 0) {
        // First child

        close(pipe_fd[0]);

        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("minishell: dup2 failed");
            _exit(1);
        }

        close(pipe_fd[1]);

        execvp(left_command[0], left_command);

        perror("minishell: command execution failed");
        _exit(127);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("minishell: fork failed");
        return;
    }

    if (pid2 == 0) {
        // Second child

        close(pipe_fd[1]);

        if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
            perror("minishell: dup2 failed");
            _exit(1);
        }

        close(pipe_fd[0]);

        execvp(right_command[0], right_command);

        perror("minishell: command execution failed");
        _exit(127);
    }

    // Parent
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}