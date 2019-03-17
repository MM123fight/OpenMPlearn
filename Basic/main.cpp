#include <omp.h>
#include <stdio.h>
#include <iostream>
#include "param.h"

//In C++, try to avoid use define: 
/* If you want to use
 * #define PI 3.14
 * use const as following
 * const right to *: pointer is constant
 * const left to *: pointer value is constant
 */

const double pi = 3.14;
const char* const authorName = "Lu Meng";

int main(int argc,char** argv){
	//Give parameters value and print the information
	if( argc < 2)
		exit_with_help();
	cmd_line(argc,argv);
	info_print();
	

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