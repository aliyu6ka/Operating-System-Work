/*
   Amauri Lopez
   CSC345-02
   Lab2 Exercise 3
   */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int value = 5;
int main(){
	pid_t pid;
	pid = fork();

	if(pid == 0){

	}
	else{
		sleep(10);
	}
	return 0;
}
