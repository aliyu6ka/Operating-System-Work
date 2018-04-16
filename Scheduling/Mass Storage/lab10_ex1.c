/* 
	Amauri Lopez
	CSC345-02
	Lab 10 Exercise 1
	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int num_cylinders = 0; /* What will read the first number from input.txt */
int num_requests = 0; /* 2nd number */
int position_start = 0;
int counter = 0;

int FCFS(int* num, int FCFS);
int SSTF(int* sortedNums, int SSTF);
int SCAN(int* sortedNums, int SCAN);
int LOOK(int* sortedNums, int LOOK);
int CSCAN(int* sortedNums, int CSCAN);
int CLOOK(int* sortedNums, int CLOOK);

int main(void){
	int num[10000]; /* Record numberrs read from input.txt */

	/* Read input.txt */
	FILE* stream = fopen("input.txt", "r");
	char line[1024];
	while(fgets(line, 1024, stream)){
		char* temp = strdup(line);
		char* tokenPtr;

		for(tokenPtr = strtok(temp, " "); tokenPtr && &tokenPtr; tokenPtr = strtok(NULL, " \n")){
			if(num_cylinders == 0){
				/* read first number as range of cylinder */
				num_cylinders = atoi(tokenPtr);
			}
				/* Fill num array with contents of file */
			else{
				/* Read second number as number of lines*/
				if(num_requests == 0)
					num_requests = atoi(tokenPtr);
				else{
					num[counter] = atoi(tokenPtr);
					counter++;
				}
			}
		}
	}
	
	position_start = num[counter - 1]; /* Last number is the start position */

	int sortedNums[counter];
	/* get this in a new array, then sort it */
	for(int i = 0; i<counter - 1;i++){
		for(int j = i+1; j<counter - 1; j++){
			int x;
			if(sortedNums[i] > sortedNums[j]){
				x = sortedNums[i];
				sortedNums[i] = sortedNums[j];
				sortedNums[j] = x;
			}
		}
	}

	/* Head movement as integers */
	int cylinder_FCFS = 0;
	int cylinder_SSTF = 0;
	int cylinder_SCAN = 0;
	int cylinder_CSCAN = 0;
	int cylinder_LOOK = 0;
	int cylinder_CLOOK = 0;

	cylinder_FCFS = FCFS(num, cylinder_FCFS);
	cylinder_SSTF = SSTF(num, cylinder_SSTF);
	cylinder_SCAN = SCAN(num, cylinder_SCAN);
	cylinder_CSCAN = CSCAN(num, cylinder_CSCAN);
	cylinder_LOOK = LOOK(num, cylinder_LOOK);
	cylinder_CLOOK = CLOOK(num, cylinder_CLOOK);

	printf("FCFS: %d\n", cylinder_FCFS);
	printf("SSTF: %d\n", cylinder_SSTF);
	printf("SCAN: %d\n", cylinder_SCAN);
	printf("LOOK: %d\n", cylinder_LOOK);
	printf("CSCAN: %d\n", cylinder_CSCAN);
	printf("CLOOK: %d\n", cylinder_CLOOK);

	/*Print to output.txt*/
	FILE* output = fopen("output.txt", "w");
	fprintf(output, "FCFS: %d\n", cylinder_FCFS);
	fprintf(output, "SSTF: %d\n", cylinder_SSTF);
	fprintf(output, "SCAN: %d\n", cylinder_SCAN);
	fprintf(output, "LOOK: %d\n", cylinder_LOOK);
	fprintf(output, "CSCAN: %d\n", cylinder_CSCAN);
	fprintf(output, "CLOOK: %d\n", cylinder_CLOOK);
	fclose(output);
}

int FCFS(int* num, int FCFS){
	FCFS = abs(position_start-num[0]);

	for(int i = 0; i<counter - 2; i++){
		FCFS = FCFS + abs(num[i] - num[i+1]);
	}

	return FCFS;
}

int SSTF(int* sortedNums, int SSTF){
	int head = position_start;
	int min = 0;
	int max = 0;
	int min_index = 0;
	int max_index = 0;
	int min_found = 0;
	int max_found = 0;

	int checked[counter];

	/* Initialize checked array with zeros */
	for(int i = 0; i<counter; i++){
		checked[i] = 0;
	}

	for(int i = 0; i<counter - 1; i++){
		for(int j = 0; j <counter - 1; j++){

			/* Find largest point that is less than the head */
			if(sortedNums[j] < head && checked[j] != 1){
				min = sortedNums[j];
				min_index = j;
			}

			/* Find smallest point greater than the head */
			else if(sortedNums[j] > head && checked[j] != 1){
				max = sortedNums[j];
				max_index = j;

				break;
			}

		}

		/* If min was not updated */
		if(min == head || min_found == 1){
			min_found = 1;
			SSTF = SSTF + abs(head - max);
			head = max;
			checked[max_index] = 1;
		}

		/* If max was not updated */
		else if(max == head || max_found == 1){
			max_found = 1;
			SSTF = SSTF + abs(head - min);
			head = min;
			checked[min_index] = 1;
		}

		/* If seek time to min is faster */
		else if(abs(head - min) < abs(head - max)){
			SSTF = SSTF + abs(head - min);
			head = min;
			checked[min_index] = 1;
		}

		else{
			SSTF = SSTF + abs(head - max);
			head = max;
			checked[max_index] = 1;
		}
	}

	return SSTF;

}

int SCAN(int* sortedNums, int SCAN){
	int min = 0;
	int max = 0;
	int min_index = 0;
	int max_index = 0;

	for(int i = 0; i<counter - 1; i++){
		if(sortedNums[i] < position_start){
			min = sortedNums[i];
			min_index = i;
		}

		else if(sortedNums[i] > position_start){
			max = sortedNums[i];
			max_index = i;
			break;
		}
	}

	/* SCAN down then up */
	if(position_start < num_cylinders/2){
		/*Cylinders from start to nearest point */
		SCAN = abs(position_start = sortedNums[min_index]);

		/* SCAN one way */
		for(int i = min_index; i>0;i--){
			SCAN = SCAN + abs(sortedNums[i] - sortedNums[i - 1]);
		}

		/* Cylinders from first point to 0 */
		/* Cylinders in opposite direction */
		SCAN = SCAN + sortedNums[0];
		SCAN = SCAN + sortedNums[max_index];

		/* SCAn opposite direction */
		for(int i = max_index; i<counter - 2; i++){
			SCAN = SCAN + abs(sortedNums[i] - sortedNums[i+1]);
		}

	}

	/* SCAN up then down */
	else{
		/* Cylinders from start to nearest point */
		SCAN = abs(position_start - sortedNums[max_index]);

		/* SCAN one way */
		for(int i = max_index; i<counter - 2; i++){
			SCAN = SCAN + abs(sortedNums[i] - sortedNums[i+1]);
		}

		SCAN = SCAN + num_cylinders - 1 - sortedNums[counter - 2];
		SCAN = SCAN + sortedNums[min_index];

		/* SCAN opposite direction */
		for(int i = min_index; i>0; i--){
			SCAN = SCAN + abs(sortedNums[i] - sortedNums[i - 1]);
		}
	}

	return SCAN;
}

int LOOK(int* sortedNums, int LOOK){
	int min = 0;
	int max = 0;
	int min_index = 0;
	int max_index = 0;

	for(int i = 0; i < counter - 1; i++){
		/* Find largest point less than start */
		if(sortedNums[i] < position_start){
			min = sortedNums[i];
			min_index = i;
		}

		/* Find smallest point greater than start */
		else if(sortedNums[i] > position_start){
			max = sortedNums[i];
			max_index = i;
			break;
		}
	}

	/*LOOK down then up */
	if(position_start < num_cylinders/2){
		/* Cylinders froms tart to nearest point */
		LOOK = abs(position_start - sortedNums[min_index]);

		/* LOOK one way */
		for(int i = min_index; i>0;i--){
			LOOK = LOOK + abs(sortedNums[i] - sortedNums[i + 1]);
		}

		LOOK = LOOK + abs(sortedNums[counter - 2] - sortedNums[min_index]);

		/*LOOK opposite direction */
		for(int i = min_index; i> 0; i--){
			LOOK = LOOK + abs(sortedNums[i] - sortedNums[i - 1]);
		}
	}

	return LOOK;
}

int CSCAN(int* sortedNums, int CSCAN){
	int min = 0;
	int max = 0;
	int min_index = 0;
	int max_index = 0;

	for(int i = 0; i<counter - 1; i++){
		/* Find largest point less than start */
		if(sortedNums[i] < position_start){
			min = sortedNums[i];
			min_index = i;
		}

		/* Find smallest point greater than start */
		else if(sortedNums[i] > position_start){
			max = sortedNums[i];
			max_index = i;
			break;
		}

	}

	/*CSCAN down */
	if(position_start < num_cylinders/2){
		/* Cylinders from start to nearest point */
		CSCAN = abs(position_start - sortedNums[min_index]);

		/* CSCAN one way */
		for(int i=min_index;i>0;i--){
			CSCAN = CSCAN + abs(sortedNums[i] - sortedNums[i - 1]);
		}

		CSCAN = CSCAN + sortedNums[0];
		CSCAN = CSCAN + (num_cylinders - 1 - sortedNums[counter - 2]);

		/* CSCAN from opposite end */
		for(int i = counter - 2; i>max_index; i--){
			CSCAN = CSCAN + abs(sortedNums[i] - sortedNums[i - 1]);
		}
	}

	/* CSCAN up */
	else{
		/* Cylinders from start to nearest pint */
		CSCAN = abs(position_start - sortedNums[max_index]);

		/* CSCAN one way */
		for(int i = max_index; i < counter -2; i++){
			CSCAN = CSCAN + abs(sortedNums[i] - sortedNums[i+1]);
		}

		CSCAN = CSCAN + abs(sortedNums[counter - 2] - num_cylinders - 1);
		CSCAN = CSCAN + abs(-1 * sortedNums[0]);

		/* CSCAN from opposite end */
		for(int i = 0; i<min_index; i++){
			CSCAN = CSCAN + abs(sortedNums[i] - sortedNums[i+1]);
		}


	}

	return CSCAN;
}

int CLOOK(int* sortedNums, int CLOOK){
	int min = 0;
	int max = 0;
	int min_index = 0;
	int max_index = 0;

	for(int i = 0; i< counter - 1; i++){
		/* Find largest point less than start */
		if(sortedNums[i] < position_start){
			min = sortedNums[i];
			min_index = i;
		}

		/* Find smallest point greater than start */
		else if(sortedNums[i] > position_start){
			max = sortedNums[i];
			max_index = i;
			break;
		}
	}

	/*CLOOK down*/
	if(position_start < num_cylinders/2){
		/* cylinders from start to nearest point */
		CLOOK = CLOOK + abs(position_start - sortedNums[min_index]);

		/* CLOOK one way */
		for(int i = min_index; i>0; i--){
			CLOOK = CLOOK + abs(sortedNums[i] - sortedNums[i - 1]);
		}

		/* CLOOK opposite direction */
		for(int i = counter - 2; i>min_index + 1; i--){
			CLOOK = CLOOK + abs(sortedNums[i] - sortedNums[i - 1]);
		}
	}

	/* CLOOK up*/
	else{
		/* Cylinders from start to nearest point */
		CLOOK = CLOOK + abs(position_start - sortedNums[max_index]);

		/*CLOOK one way */
		for(int i = max_index; i<counter - 2;i++){
			CLOOK = CLOOK + abs(sortedNums[i] - sortedNums[i+1]);
		}

		/* CLOOK from opposite end*/
		for(int i = 0; i<min_index; i++){
			CLOOK = CLOOK + abs(sortedNums[i] - sortedNums[i+1]);
		}

	}
	 return CLOOK;
}