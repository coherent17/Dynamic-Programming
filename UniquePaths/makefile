CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --track-origins=yes

BIN = UniquePaths UniquePathsWithObstacles UniquePaths_MaxProfit UniquePaths_MaxProfit_WithPath
all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./UniquePaths_MaxProfit_WithPath

clean:
	rm $(BIN)