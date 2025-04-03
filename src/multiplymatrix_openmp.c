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
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        for(int i = id; i < M_SIZE; i=i+THREAD_NUM)
        {
            int partial_sum = 0;
            for(int j = 0; j < N_SIZE; j++)
            {
                partial_sum += A[i][j] * B[j];
            }
            P[i] = partial_sum;
        }
    }

    printf("Resultant vector P:\n");
    for (int i = 0; i < M_SIZE; i++) {
        printf("P[%d] = %d\n", i, P[i]);
    }
    
    return 1;
}