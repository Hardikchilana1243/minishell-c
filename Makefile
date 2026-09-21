
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude
SRC = src/main.c src/parser.c src/builtins.c src/execute.c src/redirection.c src/pipe.c src/signals.c
TARGET = minishell

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o src/*.o

.PHONY: all run clean