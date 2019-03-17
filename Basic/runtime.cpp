#include <omp.h>
#include <stdio.h>
#include <iostream>

int main(){

	std::cout << "one is true and zero is false" << std::endl;
	std::cout << "dynamic_before:" << omp_get_dynamic() << std::endl;
	omp_set_dynamic(1);
	std::cout << "dynamic_after:" << omp_get_dynamic() << std::endl;

	std::cout << omp_get_num_procs() << std::endl;

	std::cout << "max_threads_before:" << omp_get_max_threads() << std::endl;
	omp_set_num_threads(omp_get_num_procs());
	std::cout << "max_threads_after:" << omp_get_max_threads() << std::endl;

	double time = 0.;
	double start = omp_get_wtime();
	std::cout << "in_outer: " << omp_in_parallel() << std::endl;
	#pragma omp parallel 
	{
		#pragma omp master
		{
			std::cout << "in_inner:" << omp_in_parallel() << std::endl;
		}

		#pragma omp for 
		for (int i = 0; i < 2; ++i)
		{
			int ID = omp_get_thread_num();
			printf("hello,%d\n", ID);
			printf("world,%d\n", ID);
		}
	}
	time = omp_get_wtime() - start;
	std::cout <<  " time:" << time << std::endl;
	return 0;
}