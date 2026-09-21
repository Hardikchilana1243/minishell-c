#include "shell.h"

void run_shell(void) {
    char input[INPUT_SIZE];

    while (1) {
        printf("minishell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting MiniShell...\n");
            break;
        }

        if (input[0] == '\0') {
            continue;
        }

        printf("You entered: %s\n", input);
    }
}

int main(void) {
    run_shell();
    return 0;
}
