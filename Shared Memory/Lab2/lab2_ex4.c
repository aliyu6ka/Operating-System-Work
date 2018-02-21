/* Amauri Lopez
   CSC345-02
   Lab 2 Exercise 4
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>

int main(int argc, char** argv){
	const char* name = "sharedMem";
	const int SIZE = 4096;
	int shm_fd;
	int *ptr;

	int *ip;              //index pointer for the temporary array
	int array[SIZE];
	ip = &array[0];       //point the index pointer to the first element

	//create shared memory object
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	//configure the size of the shared memory
	ftruncate(shm_fd, SIZE);

	//memory map the shared memory object
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	int n = atoi(argv[1]);

	if(n<1){
		printf("Needs to be greater than 0 please");
		return 0;
	}

	pid_t id = fork();
	int i = 0;
	if(id==0){
		while(n>1){
			i++;    //keep track of how many elements we actually care about
			*ip = n;//insert n into the current cell of the array

			if(n%2==0){
				n=n/2;
			}
			else{
				n=3*n+1;
			}

			ip++;   //move the index pointer to the next element in array
		}
		*ip = n;    //this will take care of the remaining '1' at the end

		for (int p = 0; p<i+1; p++){
			//populate the shared memory 'array'
			ptr[p] = array[p];
		}
	}
	else{
		wait(NULL);
		shm_fd = shm_open(name, O_RDONLY, 0666);
		ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		
		//print the shared memory
		while(ptr[i]!=1){ 
			printf("%d ", ptr[i]);
			i++;
		}
		//print the last element, which should be '1'
		printf("%d ", ptr[i]);


		//remove the shared memory object
		shm_unlink(name);
	}
	return 0;
}

