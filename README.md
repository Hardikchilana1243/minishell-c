# MiniShell — A Mini Unix Shell in C

## About

MiniShell is a small Unix-like shell written in C. It allows users to
run commands and demonstrates some basic concepts of how a shell works.

The project was built to understand processes, file descriptors,
redirection, pipes and basic signal handling in Linux.

## Features

- Execute external commands
- Built-in commands: `cd`, `pwd`, `help`, `exit`
- Input redirection using `<`
- Output redirection using `>` and `>>`
- Single and multiple pipes using `|`
- Basic `SIGINT` handling
- Simple error handling

## How it works

The shell follows a simple flow:

```text
Read command
    ↓
Parse command
    ↓
Check built-in / pipe / redirection
    ↓
Execute command
    ↓
Wait for process
    ↓
Show prompt again

External commands are executed using:
- fork() — creates a new process
- execvp() — runs the command
- waitpid() — waits for the process
- pipe() — connects commands
- dup2() — handles input/output redirection
Example
minishell> pwd
/root/minishell-c

minishell> echo Hello
Hello

minishell> echo hello | grep hello | wc -l
1

Redirection:
minishell> echo Hello > test.txt
minishell> cat test.txt
Hello

Project Structure
minishell-c/
├── include/
│   └── shell.h
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── execute.c
│   ├── builtins.c
│   ├── redirection.c
│   ├── pipe.c
│   └── signals.c
├── tests/
│   └── test_commands.txt
├── Makefile
├── LICENSE
├── .gitignore
└── README.md

Build and Run
Requirements:
- Linux / WSL
- GCC
- Make
Build the project:
make

Run:
./minishell

Clean build files:
make clean

Limitations
This is a basic educational shell and does not aim to provide full Bash
functionality.
Features such as background jobs, job control, command history,
advanced quoting and environment variable expansion are not included.
What I Learned
This project helped me understand:
- Process creation and execution
- Linux file descriptors
- Pipes and inter-process communication
- Input/output redirection
- Signal handling
- Basic command parsing
- Make and Git/GitHub
License
MIT License.
Author
Hardik
B.Tech Computer Science and Engineering