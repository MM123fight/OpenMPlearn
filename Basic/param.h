#include <omp.h>
#include <stdio.h>
#include <iostream>

class prob_param{

public:
	int max_iter = 1e3;
	double tol = 1e-3;
	char* data_dir;
};
prob_param param;

void exit_with_help(){
	std::cerr << "Usage: ./main (options) [data_dir]" << std::endl;
	std::cerr << "options:" << std::endl;
	std::cerr << "-m max_iter: maximum number of outer iterations (default 1000)" << std::endl;
	std::cerr << "-t tol: tolerance of norm of KKT-condition for terminiation (default: 1e-3)" << std::endl;
	exit(0);
}

void cmd_line(int argc, char** argv){

	int i;
	for(i=1;i<argc;i++){
		if( argv[i][0] != '-' )
			break;
		if( ++i >= argc )
			exit_with_help();

		switch(argv[i-1][1]){
			case 't': param.tol = atof(argv[i]);
				  break;
			case 'm': param.max_iter = atoi(argv[i]);
				  break;
			default:
				  std::cerr << "unknown option: -" << argv[i-1][1] << std::endl;
				  exit(0);
		}
	}
	
	if(i>=argc)
		exit_with_help();
	
	param.data_dir = argv[i];
}

void info_print(){
	printf("\033[40;31mInformation of algorithm: \033[0m \n");
	printf("-----------------------------------------------------------\n");
	std::cout << "Data directory: " << param.data_dir << std::endl;
	std::cout << "Maximum number of outer iterations: " << param.max_iter << std::endl;
	std::cout << "Tolerance of norm of KKT-condition for terminiation: "  << param.tol << std::endl;
	printf("-----------------------------------------------------------\n");
}
