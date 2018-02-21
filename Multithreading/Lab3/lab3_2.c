/*
	Amauri Lopez
	CSC345-02 
	Lab3_2
   */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num_in_circle;
int num_total;

void* work(void* param){
	//repeat num_total times
	for(int i=0; i<num_total;++i){
		//generate a pair of random numbers netween -1 and 1
		double x = ((double)rand() / RAND_MAX * 2.0 - 1.0);
		double y = ((double)rand() / RAND_MAX * 2.0 - 1.0);
	
		//check whether it falls within circle
		if(sqrt(x*x + y*y) < 1.0){
			//increase num_in_circle if so
			++num_in_circle;
		}
	}

	pthread_exit(0);
}

int main(int argc, char** argv){
	double est_pi;
	num_total = atoi(argv[1]);

	pthread_t tid;

	pthread_create(&tid, 0, work, NULL);

	pthread_join(tid, NULL);

	est_pi = 4.0*num_in_circle / num_total;
	printf("pi = %f\n", est_pi);
	
	return 0;
}
