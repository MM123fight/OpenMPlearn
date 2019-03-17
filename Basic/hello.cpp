#include <omp.h>
#include <stdio.h>
#include <iostream>
int main(){
	//omp_set_num_threads(1);

	double time = 0.;
	double start = omp_get_wtime();
	#pragma omp parallel for
	for (int i = 0; i < 4; ++i)
	{
		int ID = omp_get_thread_num();
		printf("hello,%d\n", ID);
		printf("world,%d\n", ID);
	}
	time = omp_get_wtime() - start;
	std::cout <<  " time:" << time << std::endl;
	return 0;
}