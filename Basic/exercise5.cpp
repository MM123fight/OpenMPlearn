#include <omp.h>
#include <stdio.h>
#include <iostream>

#define NPOINTS 1000
#define MXITR 1000
#define NUM_THREADS 4

struct d_complex{
	double r;
	double i;
};

void testpoint(d_complex& c);
struct d_complex c;
int numoutside = 0;

int main(){
	int i,j;
	double area, error, eps = 1e-5;
	#pragma omp parallel for default(shared) private(c,j) firstprivate(eps)
	for (i = 0; i < NPOINTS; ++i){
		for (j = 0; j < NPOINTS; ++j){
			c.r = - 2.0 + 2.5*(double)(i)/(double)(NPOINTS)+eps;
			c.i = 1.125*(double)(i)/(double)(NPOINTS)+eps;
			testpoint(c);
		}
	}
	area = 2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
	error = area/(double)NPOINTS;
	std::cout << "area:" << area << std::endl;

	return 0;
}

void testpoint(d_complex& c){
	struct d_complex z = c;
	int iter;
	double temp;
	for (iter = 0; iter < MXITR; ++iter){
		temp = (z.r*z.r)-(z.i*z.i) + c.r;
		z.i = z.r*z.i*2 + c.i;
		z.r = temp;
		if ((z.r*z.r + z.i*z.i) > 4.0){
			#pragma omp atomic
			numoutside++;
			break;
		}
	}
}