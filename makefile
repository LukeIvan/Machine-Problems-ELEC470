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
MATRIX_SEQ_SRC = $(SRC_DIR)/multiplymatrix_sequential.c
MATRIX_SEQ_BIN = $(BIN_DIR)/multiplymatrix_sequential
MATRIX_OMP_SRC = $(SRC_DIR)/multiplymatrix_openmp.c
MATRIX_OMP_BIN = $(BIN_DIR)/multiplymatrix_openmp
MATRIX_EPC_SRC = $(SRC_DIR)/epc_multiplymatrix.c
MATRIX_EPC_BIN = $(BIN_DIR)/epc_multiplymatrix
MATRIX_PERF_SRC = $(SRC_DIR)/performance_multiplymatrix.c
MATRIX_PERF_BIN = $(BIN_DIR)/performance_multiplymatrix
DOT_PERF_SRC = $(SRC_DIR)/performance_dotproduct.c
DOT_PERF_BIN = $(BIN_DIR)/performance_dotproduct

all: $(PTHREAD_BIN) $(SEQUENTIAL_BIN) $(OPENMP_BIN) $(MATRIX_SEQ_BIN) $(MATRIX_OMP_BIN) $(MATRIX_EPC_BIN) $(MATRIX_PERF_BIN) $(DOT_PERF_BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(PTHREAD_BIN): $(PTHREAD_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -pthread $(INCLUDES) $< -o $@

$(SEQUENTIAL_BIN): $(SEQUENTIAL_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(OPENMP_BIN): $(OPENMP_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -fopenmp $(INCLUDES) $< -o $@

$(MATRIX_SEQ_BIN): $(MATRIX_SEQ_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(MATRIX_OMP_BIN): $(MATRIX_OMP_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -fopenmp $(INCLUDES) $< -o $@

$(MATRIX_EPC_BIN): $(MATRIX_EPC_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -fopenmp $(INCLUDES) $< -o $@

$(MATRIX_PERF_BIN): $(MATRIX_PERF_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -fopenmp $(INCLUDES) $< -o $@

$(DOT_PERF_BIN): $(DOT_PERF_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -pthread -fopenmp $(INCLUDES) $< -o $@

clean:
	rm -f $(PTHREAD_BIN) $(SEQUENTIAL_BIN) $(OPENMP_BIN) $(MATRIX_SEQ_BIN) $(MATRIX_OMP_BIN) $(MATRIX_EPC_BIN) $(MATRIX_PERF_BIN) $(DOT_PERF_BIN)

.PHONY: all clean