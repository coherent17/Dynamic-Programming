CC = gcc
CFLAGS = -g -Wall
BIN = ClimbeStairs ClimbeStairsOptimized

all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./ClimbeStairs
	./ClimbeStairsOptimized

clean:
	rm $(BIN)