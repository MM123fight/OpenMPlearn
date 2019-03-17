#include <omp.h>
#include <stdio.h>
#include <iostream>
#define ARR_SIZE 600
#define STEP_SIZE 100
int main(){
	//omp_set_num_threads(1);
	int i, j, psum = 0, sum = 0;
	int start, end;
	int a[ARR_SIZE];
	
	double time = 0.;
	double time_start = omp_get_wtime();
	#pragma omp parallel private(j,start,end) firstprivate(psum)
	{
		#pragma omp for 
		for (i = 0; i < ARR_SIZE; ++i){
			a[i] = 1;
		}
		#pragma omp for 
		for (i = 0; i < ARR_SIZE; i+=STEP_SIZE)
		{
			start = i;
			end = i + STEP_SIZE;
			printf("Computing Sum(%d,%d) from %d of %d\n", start, end, 
				omp_get_thread_num(), omp_get_num_threads());
			#pragma omp task firstprivate(psum)
			{
				for (j = start; j < end; ++j){
					psum += a[j];
				}
				printf("Task computing Sum(%d,%d) = %d from %d of %d\n", start, end, psum,
					omp_get_thread_num(),omp_get_num_threads());
				#pragma omp critical
				sum += psum;
			}
		}
	}
	time = omp_get_wtime() - time_start;
	std::cout <<  " time:" << time << "sum:" << sum << std::endl;
	return 0;
}