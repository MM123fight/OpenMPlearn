#include <omp.h>
#include <stdio.h>
#include <iostream>

int main(){

	int hist_num = 4;
	int i;
	omp_lock_t hist_locks[hist_num];
	int hist[hist_num];
	int total_num = 10;
	double time = 0.;


	omp_set_num_threads(2);
	double start = omp_get_wtime();
	#pragma omp parallel private(i) 
	{
		#pragma omp master
		{
			std::cout << omp_get_num_threads() << std::endl;
		}
		#pragma omp for
		for (i = 0; i < hist_num; ++i){
			omp_init_lock(&hist_locks[i]);
			hist[i] = 0;
		}

		int label = 0 ;
		#pragma omp for 
		for (i = 0; i < total_num; ++i){
			std::cout << omp_get_thread_num();
			label = i - (i/hist_num)*hist_num;
			for (int j = 0; j < 100000000; ++j){}
			omp_set_lock(&hist_locks[label]);
			    hist[label]++;
			omp_unset_lock(&hist_locks[label]);
		}
		#pragma omp master
		{
			std::cout << std::endl;
	 	}
		#pragma omp for
		for (i = 0; i < hist_num; ++i){
			omp_destroy_lock(&hist_locks[i]);
		}
	}
	time = omp_get_wtime() - start;
	for (int i = 0; i < hist_num; ++i){
		std::cout << hist[i] << std::endl;
	}
	std::cout <<  " time:" << time << std::endl;

	return 0;
}