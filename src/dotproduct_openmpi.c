#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "../include/dotproduct.h"

int main(int argc, char *argv[]) {
    int rank, size;
    int A[VECTOR_SIZE];
    int B[VECTOR_SIZE];
    int partial_sum = 0;
    int sum = 0;
    int ops_per_thread;
    int start_id, end_id;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    ops_per_thread = VECTOR_SIZE / size;
    start_id = rank * ops_per_thread;
    end_id = (rank == size - 1) ? VECTOR_SIZE : start_id + ops_per_thread;

    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = i + 1;
        B[i] = i + 1;
    }

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    for (int i = start_id; i < end_id; i++) {
        local_dot += A[i] * B[i];
    }partial_sum
    MPI_Reduce(&partial_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        end_time = MPI_Wtime();
        printf("MPI dot product with %d processes: %f seconds\n", 
               size, end_time - start_time);
        printf("The dot product of A × B is %d\n", global_dot);
    }

    MPI_Finalize();
    return 0;
}