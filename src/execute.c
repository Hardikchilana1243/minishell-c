#include "shell.h"

void execute_command(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("minishell: fork failed");
        return;
    }

    if (pid == 0) {
        // Child process

        for (int i = 0; args[i] != NULL; i++) {

            if(strcmp(args[i], ">>") == 0) {
                if (args[i+1] == NULL) {
                    fprintf(stderr, "minishell: missing filename after >>\n");
                    _exit(2);
                }
                char *filename = args[i+1];
                if(append_output(filename) != 0) {
                    _exit(1);
                }
                args[i] = NULL;
                break;
            }
            
            // Check for output redirection: >
            if (strcmp(args[i], ">") == 0) {

                // Make sure a filename exists after >
                if (args[i + 1] == NULL) {
                    fprintf(stderr, "minishell: missing filename after >\n");
                    _exit(2);
                }

                // Save the filename
                char *filename = args[i + 1];

                // Redirect stdout to the file
                if (redirect_output(filename) != 0) {
                    _exit(1);
                }

                // Remove > and filename from arguments
                args[i] = NULL;

                break;
            }
        }

        // Execute the command
        execvp(args[0], args);

        // execvp only reaches here if execution fails
        perror("minishell: command execution failed");
        _exit(127);
    }

    // Parent process
    int status;

    while (waitpid(pid, &status, 0) < 0) {
        if (errno == EINTR) {
            continue;
        }

        perror("minishell: waitpid failed");
        break;
    }
}