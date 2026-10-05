#include "shell.h"

void execute_pipe(char **args) {
    int command_count = 1;

    
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            command_count++;
        }
    }

    
    if (command_count < 2) {
        return;
    }

   
    if (strcmp(args[0], "|") == 0) {
        fprintf(stderr, "minishell: invalid pipe syntax\n");
        return;
    }

    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            if (args[i + 1] == NULL || strcmp(args[i + 1], "|") == 0) {
                fprintf(stderr, "minishell: invalid pipe syntax\n");
                return;
            }
        }
    }

    pid_t pids[command_count];

    int input_fd = STDIN_FILENO;

    char **command_start = args;

    for (int command_index = 0; command_index < command_count; command_index++) {

        int pipe_fd[2];

       
        if (command_index < command_count - 1) {
            if (pipe(pipe_fd) == -1) {
                perror("minishell: pipe failed");
                return;
            }
        }

        
        if (command_index < command_count - 1) {
            for (int i = 0; command_start[i] != NULL; i++) {
                if (strcmp(command_start[i], "|") == 0) {
                    command_start[i] = NULL;
                    break;
                }
            }
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("minishell: fork failed");
            return;
        }

        if (pid == 0) {

            if (input_fd != STDIN_FILENO) {
                if (dup2(input_fd, STDIN_FILENO) == -1) {
                    perror("minishell: dup2 failed");
                    _exit(1);
                }

                close(input_fd);
            }

            
            if (command_index < command_count - 1) {
                close(pipe_fd[0]);

                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
                    perror("minishell: dup2 failed");
                    _exit(1);
                }

                close(pipe_fd[1]);
            }

            execvp(command_start[0], command_start);

            perror("minishell: command execution failed");
            _exit(127);
        }

        pids[command_index] = pid;

       
        if (input_fd != STDIN_FILENO) {
            close(input_fd);
        }

       \
        if (command_index < command_count - 1) {
            close(pipe_fd[1]);
            input_fd = pipe_fd[0];
        }

        
        if (command_index < command_count - 1) {
            while (*command_start != NULL) {
                command_start++;
            }

            command_start++;
        }
    }


    for (int i = 0; i < command_count; i++) {
        waitpid(pids[i], NULL, 0);
    }

    if (input_fd != STDIN_FILENO) {
        close(input_fd);
    }
}