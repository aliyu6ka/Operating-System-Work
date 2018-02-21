/*
	Amauri Lopez
	CSC345-02
	Lab3_1
   */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

int len;

int r_min;
int r_max;
float r_stdev;
float r_avg;
float r_median;

int *ip; //index pointer to our array

void* myMedian(void* param){

	//find the median
	if(len % 2 != 0){
		r_median = *(ip + (len/2));
	} else{
		r_median = (*(ip + (len/2 - 1)) + *(ip + (len/2)))/2.0;
	}

	pthread_exit(0);
	
}

void* myStDev(void* param){
	int i;
	float avg = 0.0;

	r_stdev = 0.0;

	for(i = 0;i<len;i++){
		r_stdev += (*(ip + i) * (*(ip + i)));
		avg += *(ip + i);
	}

	r_stdev /= len;
	avg /= len;

	r_stdev = sqrt(r_stdev - avg*avg);

	pthread_exit(0);
}

void* myMin(void* param){
	r_min = *(ip + 0);

	pthread_exit(0);

}

void* myMax(void* param){
	r_max = *(ip + (len-1));

	pthread_exit(0);
}

void* myAverage(void* param){
	int i;
	float sum = 0;

	r_avg = 0;
	for(i = 0; i<len; ++i){
		sum += *(ip + i);
	}
	r_avg = sum/len;

	pthread_exit(0);
}

int main(int argc, char** argv){
	int i, j;
	char *check;

	//get the length of the array
	len = argc - 1;

	//create array of size equal to amount of parameters passed
	int myArray[argc - 1];

	for(i = 0; i<len ;i++){
		check = argv[i+1];
		if(*check == '-'){
			j = 1;
			*check++;
		}
		while(*check != 0){
			if(!isdigit(*check)){
				printf("Invalid parameter entered: %c\n", *check);
				exit(1);
			}
			check++;
		}
		myArray[i] = atoi(argv[i+1]);
		printf("%d ", myArray[i]);
	}
	printf("\n");

	//sort the array
	for(i=0;i<len;i++){
		for(j=0;j<i;j++){
			if(myArray[i] < myArray[j]){
				int t = myArray[j];
				myArray[j] = myArray[i];
				myArray[i] = t;
			}
		}
	}

	//point to the array
	ip = myArray;

	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;
	pthread_t tid5;

	pthread_create(&tid1, 0, myMin, NULL);
	pthread_create(&tid2, 0, myMax, NULL);
	pthread_create(&tid3, 0, myAverage, NULL);
	pthread_create(&tid4, 0, myStDev, NULL);
	pthread_create(&tid5, 0, myMedian, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);

	printf("Min = %d\n", r_min);
	printf("Max = %d\n", r_max);
	printf("Average = %f\n", r_avg);
	printf("Standard Deviation = %f\n", r_stdev);
	printf("Median = %f\n", r_median);

	return 0;
}






