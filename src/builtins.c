#include "shell.h"

int handle_builtin(char **args) {
    if (args[0] == NULL) {
        return 0;
    }

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "minishell: cd: missing argument\n");
            return 1;
        }

        if (chdir(args[1]) != 0) {
            perror("minishell: cd");
        }

        return 1;
    }

    if (strcmp(args[0], "pwd") == 0) {
        char cwd[INPUT_SIZE];

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("minishell: pwd");
        }

        return 1;
    }

    if (strcmp(args[0], "help") == 0) {
        printf("MiniShell - Built-in Commands\n");
        printf("  cd <directory>  Change current directory\n");
        printf("  pwd             Print current directory\n");
        printf("  help            Show this help message\n");
        printf("  exit            Exit MiniShell\n");

        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return 2;
    }

    return 0;
}