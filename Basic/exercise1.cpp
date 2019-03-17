#include <omp.h>
#include <stdio.h>
#include <iostream>

static long num_steps = 100000000;
#define NUM_THREADS 4
double step;
int main(){
	double pi = 0.;
	double sum,time;
	double x;
	step = 1./(double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	double start = omp_get_wtime();
	#pragma omp parallel for reduction(+:sum) private(x)
	for (int i = 0; i < num_steps; ++i)
	{
		x = (i+0.5)*step;
		sum += 4./(1.+x*x);
	}
	pi = step * sum; 

	/*
	
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		double x, sum;
		int nthreads = omp_get_num_threads();
		for (int i = id; i < num_steps; i += nthreads)
		{
			x = (i+0.5)*step;
			sum += 4./(1.+x*x);
		}
		#pragma omp critical
		pi += sum*step;
	}
	*/
	time = omp_get_wtime() - start;
	std::cout << "pi:" << pi << " time:" << time << std::endl;
	return 0;
}