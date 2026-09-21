
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define INPUT_SIZE 1024
#define MAX_ARGS  100

void run_shell(void);
int parse_command(char *input, char **args);
int handle_builtin(char **args);
void execute_command(char **args);
void setup_signals(void);

#endif