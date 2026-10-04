#define _POSIX_C_SOURCE 200809L

#include "shell.h"

void handle_sigint(int signal) {
    (void)signal;

    write(STDOUT_FILENO, "\n", 1);
}

void setup_signals(void) {
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = handle_sigint;

    sigemptyset(&sa.sa_mask);

    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("minishell: sigaction failed");
        exit(EXIT_FAILURE);
    }
}