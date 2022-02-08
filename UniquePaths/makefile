CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --track-origins=yes

BIN = UniquePaths UniquePathsWithObstacles UniquePaths_MaxProfit
all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./UniquePaths_MaxProfit

clean:
	rm $(BIN)