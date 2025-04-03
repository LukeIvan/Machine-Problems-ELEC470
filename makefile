CC = gcc
CFLAGS = -Wall -Werror -pthread
INCLUDES = -I./include

SRC_DIR = src
BIN_DIR = binaries

PTHREAD_SRC = $(SRC_DIR)/pt1_pthread.c
PTHREAD_BIN = $(BIN_DIR)/pt1_pthread

all: $(PTHREAD_BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(PTHREAD_BIN): $(PTHREAD_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(PTHREAD_BIN)

.PHONY: all clean