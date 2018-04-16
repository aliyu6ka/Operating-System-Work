/*
	Amauri Lopez
	Darrien Pinkman
	CSC345-02
	Project 2
	*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

double total_time = 0; /* execution time for all tasks */
FILE *output; /* external file to write to */
sem_t sem; /* lock */

char* stringCopy(const char* input){
	const size_t stringSize = (strlen(input) + 1) * sizeof(char);
	char* buffer = malloc(stringSize);

	if(buffer == NULL) { return NULL;}

	return (char *)memcpy(buffer, input, stringSize);
}
 /* Function Prototypes */
void* task1(void* param);
void* task2(void* param);
void* task3(void* param);

int main(int argc, char** argv)
{
	sem_init(&sem, 0, 1);

	/* Set up threads */
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedparam;

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	int multi_flag = 0;

	/* Read for command */
	/* Run individual tasks */	
	if(strcmp(argv[1], "single") == 0)
	{
		/* Check which task to run */
		/* Run task 1 */
		if(atoi(argv[2]) == 1)
		{
			pthread_create(&thread1, 0, task1, NULL);
			pthread_join(thread1, NULL);
		}
		/* Run task 2 */
		else if(atoi(argv[2]) == 2)
		{
			pthread_create(&thread2, 0, task2, NULL);
			pthread_join(thread2, NULL);
		}
		/* Run task 3 */
		else if(atoi(argv[2]) == 3)
		{
			pthread_create(&thread3, 0, task3, NULL);
			pthread_join(thread3, NULL);
		}
		else
			printf("Command not recognized\n");
			exit(0);
	}

	/* Do Round Robin Algorithm */
	else if(strcmp(argv[1], "multi") == 0)
	{
		multi_flag = 1;
		if(strcmp(argv[2], "sched") == 0){
			if(strcmp(argv[3], "RR") == 0){
				printf("Do RR\n");
				pthread_attr_setschedpolicy(&attr, SCHED_RR);
				schedparam.sched_priority = 10;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&thread1, &attr, task1, NULL);
				pthread_create(&thread2, &attr, task2, NULL);
				pthread_create(&thread3, &attr, task3, NULL);

				pthread_join(thread1, NULL);
				pthread_join(thread2, NULL);
				pthread_join(thread3, NULL);
			}else if(strcmp(argv[3], "FIFO") == 0){
				printf("Do FIFO\n");
				pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
				schedparam.sched_priority = 10;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&thread1, &attr, task1, NULL);
				pthread_create(&thread2, &attr, task2, NULL);
				pthread_create(&thread3, &attr, task3, NULL);
				
				pthread_join(thread1, NULL);
				pthread_join(thread2, NULL);
				pthread_join(thread3, NULL);
			}else{
				printf("Invalid Command, specify which sched RR or FIFO\n");
				printf("Make sure all fields are met\n");
				multi_flag = 0;
				exit(0);

			}

		}else if(strcmp(argv[2], "priority") == 0 && argv[3] != NULL && argv[4] != NULL){

			multi_flag = 1;
			/* Use FIFO scheduling */
			pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

			/* Modify Task 1 priority */
			if(atoi(argv[3]) == 1)
			{
				/* Lower Task 1 priority */
				if(strcmp(argv[4], "low") == 0)
				{
					printf("Task 1 low\n");

					schedparam.sched_priority = 2;
					pthread_attr_setschedparam(&attr, &schedparam);
					pthread_create(&thread1, &attr, task1, NULL);
				}
				/* Raise Task 1 priority */
				else if(strcmp(argv[4], "high") == 0)
				{
					printf("Task 1 high\n");
					schedparam.sched_priority = 95;
					pthread_attr_setschedparam(&attr, &schedparam);
					pthread_create(&thread1, &attr, task1, NULL);
				}else{
					multi_flag = 0;
					printf("Invalid Command, only accept high or low priority\n");
					exit(0);
				}
				schedparam.sched_priority = 15;
				pthread_attr_setschedparam(&attr, &schedparam);

				pthread_create(&thread2, &attr, task2, NULL);
				pthread_create(&thread3, &attr, task3, NULL);
		
				pthread_join(thread1, NULL);
				pthread_join(thread2, NULL);
				pthread_join(thread3, NULL);
			}

			/* Modify Task 2 priority */
			else if(atoi(argv[3]) == 2)
			{
				/* Lower Task 2 priority */
				if(strcmp(argv[4], "low") == 0)
				{
					printf("Task 2 low\n");
					schedparam.sched_priority = 2;
					pthread_attr_setschedparam(&attr, &schedparam);
					pthread_create(&thread2, &attr, task2, NULL);
				}
				/* Raise Task 2 priority */
				else if(strcmp(argv[4], "high") == 0)
				{
					printf("Task 2 high\n");
					schedparam.sched_priority = 95;
					pthread_attr_setschedparam(&attr, &schedparam);
					pthread_create(&thread2, &attr, task2, NULL);
				}else{
					multi_flag = 0;
					printf("Invalid Command, only accept high or low priority\n");
					exit(0);
				}
				schedparam.sched_priority = 15;
				pthread_attr_setschedparam(&attr, &schedparam);

				pthread_create(&thread1, &attr, task1, NULL);
				pthread_create(&thread3, &attr, task3, NULL);
		
				pthread_join(thread1, NULL);
				pthread_join(thread2, NULL);
				pthread_join(thread3, NULL);
			}

			/* Modify Task 3 priority */
			else if(atoi(argv[3]) == 3)
			{
				/* Lower Task 3 priority */
				if(strcmp(argv[4], "low") == 0)
				{
					printf("Task 3 low\n");
					schedparam.sched_priority = 2;
					pthread_attr_setschedparam(&attr, &schedparam);
					pthread_create(&thread3, &attr, task3, NULL);
				}
				/* Raise Task 3 priority */
				else if(strcmp(argv[4], "high") == 0)
				{
					printf("Task 3 high\n");
					schedparam.sched_priority = 95;
					pthread_attr_setschedparam(&attr, &schedparam);
					pthread_create(&thread3, &attr, task3, NULL);
				}else{
					multi_flag = 0;
					printf("Invalid Command, only accept high or low priority\n");
					exit(0);
				}

				schedparam.sched_priority = 15;
				pthread_attr_setschedparam(&attr, &schedparam);

				pthread_create(&thread2, &attr, task2, NULL);
				pthread_create(&thread1, &attr, task1, NULL);
		
				pthread_join(thread1, NULL);
				pthread_join(thread2, NULL);
				pthread_join(thread3, NULL);
			}
			else{
				printf("Invalid Command, specify which task to prioritize");
				printf("Make sure all fields are met\n");
				multi_flag = 0;
				exit(0);
			}

		}else{
			printf("Invalid Command, maybe you should include sched or priority\n");
			printf("Make sure all fields are met\n");
			multi_flag = 0;
			exit(0);
		}

	}

	output = fopen("output.txt", "w");
	if (output == NULL)
	{
		printf("Error\n");
		exit(1);
	}

	if(multi_flag == 1){
		pthread_create(&thread1, 0, task1, NULL);
		pthread_create(&thread2, 0, task2, NULL);
		pthread_create(&thread3, 0, task3, NULL);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);
	}

	fprintf(output, "=== All Task Completed ===\n");
	fprintf(output, "=== All Task report start ===\n");
	fprintf(output, "RESULT: Total elapsed time: %.4f seconds\n", total_time);
	fprintf(output, "=== All Task report end ===\n");

	/* Print footer */
	printf("=== All Task Completed ===\n");
	printf("=== All Task report start ===\n");
	printf("RESULT: Total elapsed time: %.4f seconds\n", total_time);
	printf("=== All Task report end ===\n");

	sem_destroy(&sem);

}

void* task1(void* param)
{
	/* Find number of unique words in each file */

	/* set up clock to get start time */
	clock_t begin = clock();

	/* Set up directory read info */
	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	int fileCount = 0; /* tracks number of files */
	int maxindex = 640000; /* size of array of words */
	char* fileNamesArray[84]; /* array of file names */
	int uniqueWords[84]; /* array of unique words */
	char* words[maxindex]; /* array of words */
	int word_index = 0; /* index for array of words */
	
	for(int i = 0; i<maxindex; i++)
		words[i] = ","; /* fill array with dummy values */

	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type, we will look for 'v' */
			  
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */
				fileNamesArray[fileCount] = dir->d_name;
				
				char *pt; /* pointer for type conversions */

				FILE* stream = fopen(dest, "r"); /* open file in directory */
				char line[1024];

				/* start reading files line by line */
				while(fgets(line, 1024, stream))
				{
					char* lineCopy = strdup(line);
					
					char* tokenPtr;
					int n_uniqueWords = 0; /* number of unique words in this current file */

					for(tokenPtr = strtok(lineCopy, ","); tokenPtr && &tokenPtr; tokenPtr = strtok(NULL, ",\n"))
					{
						/* if the string contains a number, strip the number part of it, use base 10 */
						double num = strtol(tokenPtr, &pt, 10);

						/*pt will now be the "string" part if a number existed in the string */

						/* Check pt is same as original token, if so then it is non-numeric */
						if(tokenPtr == pt)
						{
							words[word_index] = tokenPtr; /* store strings in array */
							word_index++;
						}

						int unique = 1; /*Flag for a unique word */

						for(int outer = 1; outer < word_index; outer++)
						{
							
							for(int inner = 0; unique && inner < outer; inner++)
							{
								if(words[inner] == words[outer])
								{
									unique = 0; /* duplicate word found */
								}
							}
							if(unique)
								n_uniqueWords++;
						}
							
					}
					free(lineCopy);

					uniqueWords[fileCount] = n_uniqueWords/3;
				}
				/* update fileCount */
				fileCount++;
			}
		}


		closedir(d);

		 /* This was originally "print()" */
		sem_wait(&sem); /* lock */

		/* Print report to console */
		printf("=== T1 completed ===\n");
		printf("=== T1 report start ===\n");
		for(int i = 0; i<fileCount; i++)
		{
			printf("T1 RESULT: File %s: Total number of unique words = %d\n", fileNamesArray[i], uniqueWords[i]);
		}
		printf("T1 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
		//total_time = total_time + (double)(clock()-begin)/CLOCKS_PER_SEC;
		printf("=== T1 report end ===\n");

		/* Print report to .txt file */
		/* lets worry about printing to consol first, we will uncomment this later */

		fprintf(output, "=== T1 completed ===\n");
		fprintf(output, "=== T1 report start ===\n");
		for(int i = 0; i<fileCount; i++)
		{
			fprintf(output, "T1 RESULT: File %s: Total number of unique words = %d\n", fileNamesArray[i], uniqueWords[i]);
		}
		fprintf(output, "T1 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
		total_time = total_time + (double)(clock()-begin)/CLOCKS_PER_SEC;
		fprintf(output, "=== T1 report end ===\n");

		sem_post(&sem); /* unlock */

	}
}

void* task2(void* param)
{
	/* Find min, max, average, and variance of lengths of words in each file */

	/* Follow the same set up as task 1 */
	clock_t begin = clock();

	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	int fileCount = 0; /* track number of files */
	char* fileNamesArray[84]; /* array of file names */

	double maxuniqueWordsLength[84]; /* array of max numbers */
	double minuniqueWordsLength[84]; /* array of min numbers */
	double avguniqueWordsLength[84]; /* array of average numbers */
	double varuniqueWordsLength[84]; /* array of variance */

	int maxindex = 640000;

	double wordLengths[maxindex]; /* this is to hold all the datapoint of word lengths for each file */


	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type */
			   
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */
				fileNamesArray[fileCount] = dir->d_name;

				/* Initialize max, min, and sum of lengths of words for each file */
				double maxLength = 0;
				double minLength = 0;

				/* We will use sum later when finding the variance */
				double sum = 0;

				int currentindex = 0;

				for(int i=0; i<maxindex; i++)
					wordLengths[i] = 0;
				
				char *pt;
				char buffer[100]; /* This will be used to store the numbers as strings */

				FILE* stream = fopen(dest, "r"); /* open file in directory */
				char line[1024];

				/* Start reading the files line by line */
				while(fgets(line, 1024, stream))
				{
					char* lineCopy = strdup(line);
					char* tokenPtr;
					
					/* Get string tokens split by commas and new lines */
					for(tokenPtr = strtok(lineCopy, ","); tokenPtr && &tokenPtr; tokenPtr = strtok(NULL, ",\n"))
					{
						/* get the pure number portion of the string */
						double num = strtol(tokenPtr, &pt, 10);

						/*get this number back as a string to compare with the token, I don't think any number in a word would be more than 100 characters long */
						snprintf(buffer, 100, "%f", num);

						if(tokenPtr != buffer) /* if the token is not a pure number */
						{
							/* get the length of the word */
							double wordLength = strlen(tokenPtr);

							/* find max length of the words */
							if(maxLength == 0)
								maxLength = wordLength;
							else{
								if(maxLength < wordLength)
									maxLength = wordLength;
							}

							/* find min length of the words */
							if(minLength == 0)
								minLength = wordLength;
							else{
								if(minLength > wordLength)
									minLength = wordLength;
							}
							
							/* Record lengths of each word to calculate variance later */
							wordLengths[currentindex] = wordLength;
							currentindex++;

							/* Update the sum of the word lengths for each file */
							sum = sum + wordLength;
							
						}
							
					}
					free(lineCopy);

				}
			
				/* Set the max, min, and average of word lengths for each file */
				maxuniqueWordsLength[fileCount] = maxLength;
				minuniqueWordsLength[fileCount] = minLength;

				/* To get Average lengths, divide sum of all lengths by the number of words */
				avguniqueWordsLength[fileCount] = sum/currentindex;

				/* To get the variance, we subtract the mean from every datapoint and square the result 
				   then add all the squared values together and divide by number of datapoint minus 1*/
				for(int i=0; i<currentindex; i++)
				{
					wordLengths[i] = (wordLengths[i]-avguniqueWordsLength[fileCount])*(wordLengths[i]-avguniqueWordsLength[fileCount]);

					/* Update the variance array */
					varuniqueWordsLength[fileCount] = varuniqueWordsLength[fileCount] + wordLengths[i];
				}
				varuniqueWordsLength[fileCount] = varuniqueWordsLength[fileCount]/(currentindex - 1);
				
				fileCount++;
			}
		}

		closedir(d);

		sem_wait(&sem); /* lock */

		/* Print report to console */
		printf("=== T2 completed ===\n");
		printf("=== T2 report start ===\n");
		for(int i = 0; i<fileCount; i++)
		{
			printf("T2 RESULT: File %s: Max Word Length = %.2f, Min Word Length = %.2f, Average = %.2f, Variance = %.2f\n", fileNamesArray[i], maxuniqueWordsLength[i], minuniqueWordsLength[i], avguniqueWordsLength[i], varuniqueWordsLength[i]);
		}
		printf("T2 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
		//total_time = total_time + (double)(clock()-begin)/CLOCKS_PER_SEC;
		printf("=== T2 report end ===\n");

		/* Print report to .txt file */
		fprintf(output, "=== T2 completed ===\n");
		fprintf(output, "=== T2 report start ===\n");
		for(int i = 0; i<fileCount; i++)
		{
			fprintf(output, "T2 RESULT: File %s: Max = %.2f, Min = %.2f, Avg = %.2f, Var = %.2f\n", fileNamesArray[i], maxuniqueWordsLength[i], minuniqueWordsLength[i], avguniqueWordsLength[i], varuniqueWordsLength[i]);
		}
		fprintf(output, "T2 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
		total_time = total_time + (double)(clock()-begin)/CLOCKS_PER_SEC;
		fprintf(output, "=== T2 report end ===\n");
		fprintf(output, "\n");

		sem_post(&sem); /* unlock */

	}
}

void* task3(void* param)
{
	/* Find min, max, and average of rows and columns of all files */
	/* Also find ratio of missing or zero values in each file */

	clock_t begin = clock();
	
	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	int minRow = 0;
	int rowMax = 0;
	double rowTotal = 0;
	int columnMin = 0;
	int columnMax = 0; 
	double columnTotal = 0;
	int fileCount = 0;
	double ratios[84];
	char* fileNamesArray[84];

	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type */
			   
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */

				fileNamesArray[fileCount] = dir->d_name;
			
				/* Initialize Rows and columns for each file */
				int rows = 0;
				int columns = 0;

				/*Initialize Non Zero Count */
				char* pt;
				int non_zero_Count = 0;

				FILE* stream = fopen(dest, "r"); /* open file in directory */
				char line[1024];

				/* Start reading file line by line */
				while(fgets(line, 1024, stream))
				{
					char* lineCopy = strdup(line);

					int x = 0; /* This will temporarily hold amount of columns for this file*/
					char* tokenPtr;

					/* This time, for every comma we see, we just add to amount of columns */
					for(tokenPtr = strtok(lineCopy, ","); tokenPtr && &tokenPtr; tokenPtr = strtok(NULL, ",\n")){
						x++; /* count columns in line */

						double num = strtol(tokenPtr, &pt, 10);

						/* Check if what is in buffer is still the string portion */
						if(tokenPtr == pt){

							/* Found a nonzero, because strings are nonzero */
							non_zero_Count++;
						}else if(num != 0){

							/* If it was just a number, and the number is not zero, then we found another one */
							non_zero_Count++;
						}

						/* If it's alphanumeric, then check if it is a decimal*/
						else if(tokenPtr[1] == '.'){
							int j = 0;
							int notzero = 0;

							/* check if it is a decimal of zeroes */
							while(j<strlen(tokenPtr)){
								if(tokenPtr[j] != 0 || tokenPtr[j] != '.'){	
									notzero = 1;
								}
								j++;
							}

							/* If the not-zero flag is still true, then non zero found */
							if(notzero = 1)
								non_zero_Count++;
						}
						

					}

					free(lineCopy);
					if(columns == 0)
						columns = x;	

					rows++; /* count lines in stream every time we do an fgets, because it reads line by line */
				}

				/* Find min rows, similar to task 2*/
				if(minRow == 0)
					minRow = rows;
				else{
					if(minRow > rows)
						minRow = rows;
				}

				/* Find max rows */
				if(rowMax == 0)
					rowMax = rows;
				else{
					if(rowMax < rows)
						rowMax = rows;
				}

				/* Find min columns */
				if(columnMin == 0)
					columnMin = columns;
				else{
					if(columnMin > columns)
						columnMin = columns;
				}

				/* Find max columns */
				if(columnMax == 0)
					columnMax = columns;
				else{
					if(columnMax < columns)
						columnMax = columns;
				}

				/* Update rowTotal and columnTotal */
				rowTotal = rowTotal + rows;
				columnTotal = columnTotal + columns;

				/* Find the ratio of non-zero to total (columns*rows) */
				ratios[fileCount] = ((double)(100*(rows*columns - non_zero_Count))/(double)(rows*columns));
				fileCount++;
				
			}
		}

		closedir(d);

		sem_wait(&sem); /* lock */

		/* Print report to console */
		printf("=== T3 completed ===\n");
		printf("=== T3 report start ===\n");
		printf("T3 RESULT: Rows: Max = %d, Min = %d, Avg = %.2f\n", rowMax, minRow, rowTotal/fileCount);
		printf("T3 RESULT: Cols: Max = %d, Min = %d, Avg = %.2f\n", columnMax, columnMin, columnTotal/fileCount);

		for(int i = 0; i<fileCount; i++){
			printf("T3 RESULT: File: %s: Ratio: %.2f%%\n", fileNamesArray[i], ratios[i]);
		}

		printf("T3 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
		//total_time = total_time + (double)(clock()-begin)/CLOCKS_PER_SEC;
		printf("=== T3 report end ===\n");
		printf("\n");

		/* Print report to .txt file */
		fprintf(output, "=== T3 completed ===\n");
		fprintf(output, "=== T3 report start ===\n");
		fprintf(output, "T3 RESULT: Rows: Max = %d, Min = %d, Avg = %.2f\n", rowMax, minRow, rowTotal/fileCount);
		fprintf(output, "T3 RESULT: Cols: Max = %d, Min = %d, Avg = %.2f\n", columnMax, columnMin, columnTotal/fileCount);

		for(int i = 0; i<fileCount; i++){
			fprintf(output, "T3 RESULT: File: %s: Ratio: %.2f%%\n", fileNamesArray[i], ratios[i]);
		}

		fprintf(output, "T3 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
		total_time = total_time + (double)(clock()-begin)/CLOCKS_PER_SEC;
		fprintf(output, "=== T3 report end ===\n");
		fprintf(output, "\n");

		sem_post(&sem); /* unlock */
	}
}

