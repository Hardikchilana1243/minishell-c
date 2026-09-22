
#include "shell.h"

int parse_command(char *input, char **args) {
    int argc = 0;

    char *token = strtok(input, " \t\n");

    while (token != NULL && argc < MAX_ARGS - 1) {
        args[argc] = token;
        argc++;

        token = strtok(NULL, " \t\n");
    }

    args[argc] = NULL;

    return argc;
}