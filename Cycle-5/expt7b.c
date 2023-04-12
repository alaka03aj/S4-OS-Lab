#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<sys/shm.h>  
#include<string.h>  
int main()  
{  
	int i;  
	void *shared_memory1;  
	char buff[100];  
	int shmid;  
	shmid = shmget((key_t)2345, 1024, 0666);  
	printf("Key of shared memory is %d\n",shmid);  
	shared_memory1 = shmat(shmid,NULL,0); //process attached to shared memory segment  
	printf("Process attached at %p\n",shared_memory1);  
	printf("Data read from shared memory is : %s\n",(char *)shared_memory1);
}  
