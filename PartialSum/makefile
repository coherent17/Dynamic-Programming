CC = gcc
CFLAGS = -g -Wall
BIN = PartialSum

all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./$(BIN)

clean:
	rm $(BIN)