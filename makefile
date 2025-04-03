CC = gcc
CFLAGS = -Wall -Werror
INCLUDES = -I./include

SRC_DIR = src
BIN_DIR = binaries

PTHREAD_SRC = $(SRC_DIR)/dotproduct_pthread.c
PTHREAD_BIN = $(BIN_DIR)/dotproduct_pthread

SEQUENTIAL_SRC = $(SRC_DIR)/dotproduct_sequential.c
SEQUENTIAL_BIN = $(BIN_DIR)/dotproduct_sequential

OPENMP_SRC = $(SRC_DIR)/dotproduct_openmp.c
OPENMP_BIN = $(BIN_DIR)/dotproduct_openmp

all: $(PTHREAD_BIN) $(SEQUENTIAL_BIN) $(OPENMP_BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(PTHREAD_BIN): $(PTHREAD_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -pthread $(INCLUDES) $< -o $@

$(SEQUENTIAL_BIN): $(SEQUENTIAL_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(OPENMP_BIN): $(OPENMP_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -fopenmp $(INCLUDES) $< -o $@

clean:
	rm -f $(PTHREAD_BIN) $(SEQUENTIAL_BIN) $(OPENMP_BIN)

.PHONY: all clean