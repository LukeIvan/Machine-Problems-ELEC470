#include <stdio.h>
#include "../include/dotproduct_pthread.h"

int dotproduct = 0;
int A[VECTOR_SIZE];
int B[VECTOR_SIZE];

int main()
{
    for(int i = 0; i < VECTOR_SIZE; i++) // Initialize A & B
    {
        A[i] = i+1;
        B[i] = i+1;
    }

    for(int i = 0; i < VECTOR_SIZE; i++)
    {
        dotproduct+= A[i]*B[i];
    }
    printf("The dot product of A x B is %d\n", dotproduct);
    return 1;
}