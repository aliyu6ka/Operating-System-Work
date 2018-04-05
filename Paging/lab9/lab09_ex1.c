/* 
	Amauri Lopez
	CSC345-02
	Lab 9 Exercise 1
	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int replacement_idx = 0;
int idx = 0;

int page_clear(int* page, int numPageFrames){
	/* Clear the replacement array and fill with dummy values */
	for(int i = 0; i< numPageFrames; i++){
		page[i] = -1;
	}
	replacement_idx = 0;
}

int fault_FIFO(int* page, int numPageFrames, int* input){

	int FIFO_faults = 0;
	for(int j = 1; j < idx; j++){
		int match = 0;

		/* look through contents of input and compare */
		for(int i = 0; i< numPageFrames; i++){
			if(input[j] == page[i])
				match = 1;
		}

		/* If no match is found, then populate and replace the contents */
		if(match == 0){
			page[replacement_idx] = input[j];

			/* Cycle through to next replacement index */
			if(replacement_idx < numPageFrames - 1)
				replacement_idx++;
			else
				replacement_idx = 0;

			/* Mark this as a fault */
			FIFO_faults++;
		}
	}

	return FIFO_faults;

}

int fault_LRU(int* page, int numPageFrames, int* input){
	
	int LRU_faults = 0;	
	
	int cellUsage[numPageFrames]; /* Create an array to keep track of each page frame's usage frequency */

	/* Least recently used will start off with the first cell being the least */
	for(int i = 0; i < numPageFrames; i++){
		cellUsage[i] = i;
	}

	for(int j = 1; j<idx; j++){
		int match = 0;

		/* look through contents of input and compare */
		for(int i = 0; i< numPageFrames; i++){
			if(input[j] == page[i]){
				match = 1;

				/* decrement all usage frequencies, and set the current index to most recently used (highest frequency) */
				for(int h = 0; h < numPageFrames; h++){
					cellUsage[h]--;

				}
				cellUsage[i] = numPageFrames - 1;
			}
		}

		/* If no match is found, then replace the contents */
		if(match == 0){
			/* get the least recently used index */
			replacement_idx = 0;
			int least = 0;

			/* The least recently used index will be the index containing the lowest frequency of 0*/
			for(int i = 0; i< numPageFrames; i++){
				if(replacement_idx >= cellUsage[i])
					least = i;
			}

			replacement_idx = least;

			page[replacement_idx] = input[j];

			/* decrement all usage frequencies */
			for(int h = 0; h< numPageFrames; h++){
				cellUsage[h]--;

			}
			cellUsage[replacement_idx] = numPageFrames - 1;

			/* Mark this as a fault */
			LRU_faults++;
		}

	}

	return LRU_faults;	
}

int fault_Optimal(int* page, int numPageFrames, int* input){

	int Optimal_faults = 0;
	
	int futureValues[numPageFrames]; /* Array to hold a "weight" for each page frame, higher weight means it will be used in the future more */

	for(int j = 1; j<idx;j++){

		/* Fill up the future values with dummy values for now */
		for(int i = 0; i< numPageFrames; i++)
			futureValues[i] = 0;

		int match = 0;

		/* compare input with contents of page */
		for(int i = 0; i<numPageFrames;i++){
			if(input[j] == page[i])
				match = 1;

		}

		/* If no match is found, then replace contents */
		if(match == 0){

			 /* Find out when each of the page frames will be used again */
			for(int i = 0; i< numPageFrames; i++){

				for(int h = j; h<idx; h++){
					futureValues[i]++;

					/* If the current frame is going to be used again in the future, then break and use */
					if(page[i] == input[h]){
						break;
					}
					else if(h == idx - 1){
						/* if we did not find a future instance of the page reference */
						futureValues[i]++;
					}
				}
			}

			/* Get the proper replacement index */
			replacement_idx = 0;
			int max = 0;
			for(int i = 0; i< numPageFrames; i++){
				 /* Find the page that is used furthest in the future */
				if(max < futureValues[i]){
					max = futureValues[i];
					replacement_idx = i;
				}

				/* If there happens to be more than one page that are equally as far in the future */
				else if(max == futureValues[i]){
					/* If the previous index is occupied then we can replace it
						if not, then we cannot replace it because it would be in the
						special case when the page array is not fully occupied yet */
					if(page[i-1] != -1){
						replacement_idx = i;
					}
				}
			}

			page[replacement_idx] = input[j];
			Optimal_faults++;
		}
	}

	return Optimal_faults;
}

int main(){

	char line[1024];
	char* fileName = "input.txt";

	int numPageFrames = 0;
	int input[100]; /*Array to read in input.txt*/

	FILE* stream = fopen(fileName, "r");

	/* start reading files line by line */
	while(fgets(line, 1024, stream)){
		char* lineCopy = strdup(line);
		char* tokenPtr;

		for(tokenPtr = strtok(lineCopy, " "); tokenPtr && &tokenPtr; tokenPtr = strtok(NULL, " \n")){
			/* First number is going to be number of page frames */
			if(numPageFrames == 0)
				numPageFrames = atoi(tokenPtr);

			/* Once numPageFrames is accounted, fill up input array with contents of input.txt */
			if(numPageFrames != 0){
				input[idx] = atoi(tokenPtr);
				idx++;
			}
		}
	}

	int page[numPageFrames]; /* Array to simulate the page replacement array */

	page_clear(page, numPageFrames);
	int FIFO_faults = fault_FIFO(page, numPageFrames, input);

	page_clear(page, numPageFrames);
	int LRU_faults = fault_LRU(page, numPageFrames, input);

	page_clear(page, numPageFrames);
	int Optimal_faults = fault_Optimal(page, numPageFrames, input);

	
	/* RESULTS */
	printf("FIFO: %d\n", FIFO_faults);
	printf("LRU: %d\n", LRU_faults);
	printf("Optimal: %d\n", Optimal_faults);

	/*Print to output.txt*/
	FILE* output = fopen("output.txt", "w");
	fprintf(output, "FIFO: %d\n", FIFO_faults);
	fprintf(output, "LRU: %d\n", LRU_faults);
	fprintf(output, "Optimal: %d\n", Optimal_faults);
	fclose(output);


}
