#include <stdio.h>
#include <pthread.h>
#include "../include/dotproduct_pthread.h"

pthread_mutex_t mutex1;
int dotproduct = 0;
int A[VECTOR_SIZE];
int B[VECTOR_SIZE];
int thread_nos[THREAD_NUM];

void *dotprod(void *args)
{
    int thread_number = *((int*)args);
    int partial_sum = 0;
    for(int i = OPS_PER_THREAD*thread_number; i < OPS_PER_THREAD*(thread_number+1); i++)
    {
        partial_sum += A[i]*B[i];
    }
    pthread_mutex_lock(&mutex1);
    dotproduct = dotproduct + partial_sum;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

int main()
{
    for(int i = 0; i < VECTOR_SIZE; i++) // Initialize A & B
    {
        A[i] = i+1;
        B[i] = i+1;
    }

    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex1, NULL);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        thread_nos[i] = i;
        if(pthread_create(&thread[i], NULL, dotprod, &thread_nos[i]) != 0)
        {
            perror("Pthread_create failure!");
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            char* str = "Pthread_join failure for thread number: %d";
            char msg[64];
            sprintf(msg, str, i);
            perror(msg);
        }
    }
    printf("The dot product of A x B is %d\n", dotproduct);
    return 1;
}