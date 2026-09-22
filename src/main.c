
#include "shell.h"

void run_shell(void) {
    char input[INPUT_SIZE];
    char *args[MAX_ARGS];

    while (1) {
        printf("minishell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        int argc = parse_command(input, args);

        if (argc == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            printf("Exiting MiniShell...\n");
            break;
        }

        execute_command(args);
    }
}

int main(void) {
    run_shell();
    return 0;
}