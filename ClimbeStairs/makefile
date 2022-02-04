CC = gcc
CFLAGS = -g -Wall
BIN = ClimbeStairs ClimbeStairs_2_steps_SpatialOptimized ClimbeStairs_3_steps ClimbeStairs_k_steps ClimbeStairs_k_steps_SpatialOptimized ClimbeStairs_k_steps_skipStairs

all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(BIN)