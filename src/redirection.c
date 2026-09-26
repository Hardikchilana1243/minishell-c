#include "shell.h"

int redirect_output(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("minishell: open");
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("minishell: dup2");
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}