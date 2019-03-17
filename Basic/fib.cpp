#include <omp.h>
#include <stdio.h>
#include <iostream>
int fib(int n);

int main(){
	int size = 10;
	double x[size];
	#pragma omp parallel for
	for (int i = 0; i < 10; ++i){
		x[i] = i;
		for (int j = 0; j < 3; ++j){
			x[i] += j/10.;
		}
	}

	for (int i = 0; i < 10; ++i){
		std::cout << x[i] << std::endl;
	}

	#pragma omp parallel	
	{
    	#pragma omp single
		std::cout << fib(10) << std::endl;
	}

	return 0;
}

int fib(int n){
	int x,y;
	if( n < 2) return n;
	#pragma omp task shared(x)
	 x = fib(n-1);
	#pragma omp task shared(y)
	 y = fib(n-2);
	#pragma omp taskwait
	 return x+y;
}