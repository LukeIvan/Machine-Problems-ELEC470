#include <omp.h>
#include <stdio.h>
#include "../include/multiplymatrix.h"

int A[M_SIZE][N_SIZE];
int B[N_SIZE];
int P[M_SIZE];

void init()
{
    for (int i = 0; i < M_SIZE; i++) 
        for (int j = 0; j < N_SIZE; j++) A[i][j] = i + j;

    for (int j = 0; j < N_SIZE; j++) B[j] = j;
    
    for (int i = 0; i < M_SIZE; i++) P[i] = 0;
}

int main()
{
    init();
    omp_set_num_threads(THREAD_NUM);
    for (int i = 0; i < M_SIZE; i++) {
        int sum = 0;
        
        #pragma omp parallel for reduction(+:sum)
        for (int j = 0; j < N_SIZE; j++) {
            sum += A[i][j] * B[j];
        }
        P[i] = sum;
    }

    printf("Resultant vector P:\n");
    for (int i = 0; i < M_SIZE; i++) {
        printf("P[%d] = %d\n", i, P[i]);
    }
    
    return 1;
}