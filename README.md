# MiniShell — A Mini Unix Shell in C

## Project Description

MiniShell is a lightweight, Unix-like command-line interpreter developed in C. It provides an interactive environment where users can enter commands, execute external programs and perform basic file operations.

The project aims to demonstrate fundamental operating-system concepts such as process creation, program execution, file descriptors, input/output redirection and inter-process communication.

MiniShell is designed as an educational project and is not intended to be a full replacement for Bash or other production shells.

## Goals

* Understand how command-line shells work internally.
* Learn process creation and execution using POSIX system calls.
* Implement command parsing and argument handling in C.
* Understand file descriptors and input/output redirection.
* Implement basic inter-process communication using pipes.
* Practice modular programming, error handling, testing and documentation.

## Specifications

### Functional Requirements

1. Display an interactive shell prompt.
2. Read and parse user commands.
3. Execute external programs using `fork()` and `execvp()`.
4. Support the built-in commands `cd`, `pwd`, `help` and `exit`.
5. Support input redirection using `<`.
6. Support output redirection using `>` and `>>`.
7. Support a single pipeline between two commands using `|`.
8. Handle common errors, end-of-input and basic interrupt signals.

### Non-Functional Requirements

* The implementation will be written in C.
* The project will target Linux and WSL environments.
* The code will be divided into manageable modules.
* System-call failures and invalid commands will be handled gracefully.
* The program will be buildable using GCC and Make.

## Design

The shell follows a simple command-processing pipeline:

1. Display the prompt and read input.
2. Parse the input into a command and its arguments.
3. Identify built-in commands and special operators.
4. Execute the appropriate built-in or external program.
5. Apply redirection or pipeline handling when requested.
6. Wait for child processes and return to the prompt.

### Main Modules

* `main.c`: Shell initialization, input loop and prompt.
* `parser.c`: Command tokenization and operator recognition.
* `execute.c`: Process creation, external execution and waiting.
* `builtins.c`: Built-in command implementations.
* `redirection.c`: Input and output redirection.
* `signals.c`: Basic signal handling.
* `shell.h`: Shared declarations and definitions.

## Technology Stack

* Language: C
* Compiler: GCC
* Platform: Linux / Windows Subsystem for Linux (WSL)
* Build system: Make
* Version control: Git and GitHub
* System interfaces: POSIX process, file and pipe APIs

## Testing Strategy

The project will be tested using:

* Valid and invalid external commands.
* Built-in commands and directory changes.
* Empty input and end-of-file.
* Input, overwrite and append redirection.
* Single-pipeline command execution.
* Missing files, invalid paths and interrupted commands.
* Verification that redirected and piped output is correct.

## Limitations

The initial implementation will not provide full Bash compatibility. Advanced shell scripting, command substitution, complex quoting, environment-variable expansion, background jobs and complete job control are outside the required scope.

## Future Scope

* Multiple pipeline stages.
* Command history and history navigation.
* Background execution and job management.
* Environment-variable expansion.
* Quoting and escape-sequence support.
* Tab completion.

## Expected Outcome

A functional, modular command-line shell that demonstrates basic process management, command parsing, file handling and inter-process communication in C.

## Author

* Name: [Your Name]
* Course: B.Tech Computer Science and Engineering
* Project: MiniShell — A Mini Unix Shell in C

## Build and Run

```bash
make
./minishell
```

## License

For educational use. Add an appropriate license before public distribution.
