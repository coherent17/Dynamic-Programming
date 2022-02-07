CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

BIN = UniquePaths
all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./UniquePaths

clean:
	rm $(BIN)