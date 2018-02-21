/*
   Amauri Lopez
   CSC345-02
   Lab2 Exercise 1
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int value = 5;
int main(){
	pid_t pid; //parent id object
	pid = fork();
	if(pid = 0){ //child process
		value += 15;
		printf("CHILD: value = %d", value);
		return 0;
	}
	else if(pid>0){ //parent process
		wait(NULL);
		printf("PARENT: value = %d", value); //LINE A
		return 0;
	}
}
