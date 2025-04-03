#include <stdio.h>
#include <omp.h>
#include "../include/dotproduct.h"

int A[VECTOR_SIZE];
int B[VECTOR_SIZE];

int main()
{
    int dotproduct = 0;
    
    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = i;
        B[i] = i;
    }
    omp_set_num_threads(THREAD_NUM);
    #pragma omp parallel // Parallel region
    {
        int partial_sum = 0;
        int id = omp_get_thread_num();
        
        for (int i = id; i < VECTOR_SIZE; i=i+THREAD_NUM) {
            partial_sum += A[i] * B[i];
        }
        #pragma omp critical
        {
            dotproduct += partial_sum;
        }
    }
    
    printf("The dot product of A x B is %d\n", dotproduct);
    return 0;
}