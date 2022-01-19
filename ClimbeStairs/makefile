CC = gcc
CFLAGS = -g -Wall
BIN = ClimbeStairs

all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./$(BIN)

clean:
	rm $(BIN)