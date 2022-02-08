CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

BIN = UniquePaths UniquePathsWithObstacles
all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./UniquePathsWithObstacles

clean:
	rm $(BIN)