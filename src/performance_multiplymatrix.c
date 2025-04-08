#include <omp.h>
#include <stdio.h>
#include "../include/multiplymatrix.h"

int A[M_SIZE][N_SIZE];
int B[N_SIZE];
int P[M_SIZE];

void init() {
    for (int i = 0; i < M_SIZE; i++)
        for (int j = 0; j < N_SIZE; j++) A[i][j] = i + j;
    for (int j = 0; j < N_SIZE; j++) B[j] = j;
    for (int i = 0; i < M_SIZE; i++) P[i] = 0;
}

void run() {
    omp_set_num_threads(THREAD_NUM);
    for (int i = 0; i < M_SIZE; i++) {
        int sum = 0;
        #pragma omp parallel for reduction(+:sum)
        for (int j = 0; j < N_SIZE; j++) {
            sum += A[i][j] * B[j];
        }
        P[i] = sum;
    }
}

void run_sequential() {
    for (int i = 0; i < M_SIZE; i++) {
        for (int j = 0; j < N_SIZE; j++) {
            P[i] += A[i][j] * B[j];
        }
    }
}

void print_results() {
    printf("Resultant vector P:\n");
    for (int i = 0; i < M_SIZE; i++) {
        printf("P[%d] = %d\n", i, P[i]);
    }
}

int main() {
    double start_time, end_time;
    
    init();
    
    start_time = omp_get_wtime();
    run();
    end_time = omp_get_wtime();
    printf("Parallel implementation time: %f seconds\n", end_time - start_time);
    print_results();
    
    for (int i = 0; i < M_SIZE; i++) P[i] = 0;
    
    start_time = omp_get_wtime();
    run_sequential();
    end_time = omp_get_wtime();
    printf("Sequential implementation time: %f seconds\n", end_time - start_time);
    print_results();
    
    return 1;
}