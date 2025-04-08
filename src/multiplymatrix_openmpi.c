#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "../include/multiplymatrix.h"

int main(int argc, char *argv[]) 
{
    int rank, size;
    int A[M_SIZE][N_SIZE];
    int B[N_SIZE];
    int P[M_SIZE];
    int local_P[M_SIZE];
    int rows_per_proc, start_row, end_row;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    rows_per_proc = M_SIZE / size;
    start_row = rank * rows_per_proc;
    end_row = (rank == size - 1) ? M_SIZE : start_row + rows_per_proc;

    for (int i = 0; i < M_SIZE; i++) {
        local_P[i] = 0;
        if (rank == 0) {
            P[i] = 0;  
        }
    }

    for (int i = 0; i < M_SIZE; i++) {
        for (int j = 0; j < N_SIZE; j++) {
            A[i][j] = i + j;
        }
    }
    
    for (int j = 0; j < N_SIZE; j++) {
        B[j] = j;
    }

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N_SIZE; j++) {
            local_P[i] += A[i][j] * B[j];
        }
    }

    MPI_Reduce(local_P, P, M_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end_time = MPI_Wtime();
        printf("MPI implementation time with %d processes: %f seconds\n", 
               size, end_time - start_time);
        
        printf("Resultant vector P:\n");
        for (int i = 0; i < M_SIZE; i++) {
            printf("P[%d] = %d\n", i, P[i]);
        }
    }

    MPI_Finalize();
    return 0;
}