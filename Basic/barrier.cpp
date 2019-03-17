#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#define NUM_THREADS 4

int main(){

	omp_set_num_threads(NUM_THREADS);
	int i, n =6;
    #pragma omp parallel private(i) shared(n)
    {
        #pragma omp for nowait
        for(i = 0; i < n; i++) {
            printf("thread %d: +\n", omp_get_thread_num());
        }
        #pragma omp for
        for(i = 0; i < n; i++) {
            printf("thread %d: -\n", omp_get_thread_num());
        }
    }


    #pragma omp parallel for default(none) schedule(static, 2)  private(i) shared(n)
    for(i = 0; i < n; i++) {
        printf("Iteration %d executed by thread %d\n", i, omp_get_thread_num());
    }

	return 0;
}