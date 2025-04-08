#include <stdio.h>
#include <pthread.h>
#include <omp.h>
#include "../include/dotproduct.h"

pthread_mutex_t mutex1;
int dotproduct = 0;
int A[VECTOR_SIZE];
int B[VECTOR_SIZE];
int thread_nos[THREAD_NUM];

void init() {
    for(int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = i+1;
        B[i] = i+1;
    }
    dotproduct = 0;
}

void *dotprod_pthread(void *args) {
    int thread_number = *((int*)args);
    int partial_sum = 0;
    for(int i = OPS_PER_THREAD*thread_number; i < OPS_PER_THREAD*(thread_number+1); i++) {
        partial_sum += A[i]*B[i];
    }
    pthread_mutex_lock(&mutex1);
    dotproduct = dotproduct + partial_sum;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void run_pthread() {
    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex1, NULL);
    
    for (int i = 0; i < THREAD_NUM; i++) {
        thread_nos[i] = i;
        if(pthread_create(&thread[i], NULL, dotprod_pthread, &thread_nos[i]) != 0) {
            perror("Pthread_create failure!");
        }
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        if(pthread_join(thread[i], NULL) != 0) {
            char* str = "Pthread_join failure for thread number: %d";
            char msg[64];
            sprintf(msg, str, i);
            perror(msg);
        }
    }
}

void run_openmp() {
    dotproduct = 0;
    omp_set_num_threads(THREAD_NUM);
    
    #pragma omp parallel
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
}

void run_sequential() {
    dotproduct = 0;
    for(int i = 0; i < VECTOR_SIZE; i++) {
        dotproduct += A[i]*B[i];
    }
}

void print_result(const char* method_name) {
    printf("The dot product of A x B using %s is %d\n", method_name, dotproduct);
}

int main() {
    double start_time, end_time;
    
    init();
    
    start_time = omp_get_wtime();
    run_sequential();
    end_time = omp_get_wtime();
    printf("Sequential implementation time: %f seconds\n", end_time - start_time);
    print_result("Sequential");
    
    init();
    
    start_time = omp_get_wtime();
    run_openmp();
    end_time = omp_get_wtime();
    printf("OpenMP implementation time: %f seconds\n", end_time - start_time);
    print_result("OpenMP");
    
    init();
    
    start_time = omp_get_wtime();
    run_pthread();
    end_time = omp_get_wtime();
    printf("Pthread implementation time: %f seconds\n", end_time - start_time);
    print_result("Pthread");
    
    return 1;
}