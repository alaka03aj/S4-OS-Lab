#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>													//standard library for unix/ unix-like systems

void main(){
	int pid;
	pid = fork();													//creates a copy of process called child process
	if (pid<0){														//fork not created
		printf("Fork not done. Error.");
		exit(0);
	}																//fork created-> pid of child is given to pid of parent process 																		and 0 to pid of child process
	else if (pid==0){												//child process has pid 0
		printf("Child pid: %d. ppid: %d\n", getpid(),getppid());	//getpid() -> gets pid		getppid() ->gets pid of parent of 																			current process
		exit(0);
	}
	else{															//pid > 0 means its a parent process
		printf("Parent pid: %d. ", getpid());						
		printf("Child pid: %d\n", pid);								//child pid is in pid as this is the parent process
	}
}
