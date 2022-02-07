CC = gcc
CFLAGS = -g -Wall
BIN = UniquePaths
all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(BIN)