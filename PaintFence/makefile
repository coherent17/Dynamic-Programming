CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --track-origins=yes

BIN = PaintFence
all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./PaintFence

clean:
	rm $(BIN)