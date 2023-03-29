//write a C-program to implement the producer – consumer problem using semaphores

#include <stdio.h>
#include <stdlib.h>
#define size 10

int mutex = 1;		//value shared by the process
int full=0, empty = size, x = 0;

int wait(int s){
	return --s;
}

int signal(int s){
	return ++s;
}

void producer(){
	mutex=wait(mutex);
	empty = wait(empty);
	full = signal(full);
	mutex = signal(mutex);
	x++;
	printf("Producer produces item: %d\n",x);
}

void consumer(){
	mutex = wait(mutex);
	full = wait(full);
	mutex = signal(mutex);
	empty = signal(empty);
	printf("Consumer comsumes: %d\n",x);
	x--;
}


void main(){
	int n, i;
	printf("\n1. Press 1 for Producer\n2. Press 2 for Consume\n3. Press 3 for Exit");
	
    for (i = 1; i > 0; i++) {
        printf("\nEnter your choice:");
        scanf("%d", &n);
 
        // Switch Cases
        switch (n) {
        case 1:
            if ((mutex == 1)&& (empty != 0))
                producer();		// If mutex is 1 and empty is non-zero, then it is possible to produce
            
            else 		
                printf("Buffer is full!");		// Otherwise, print buffer is full
            break;
 
        case 2:
            if ((mutex == 1)&& (full != 0))
                consumer();		// If mutex is 1 and full is non-zero, then it is possible to consume
 
            else 
                printf("Buffer is empty!");		// Otherwise, print Buffer is empty
            break;
 
        // Exit Condition
        case 3:
            exit(0);
            break;
        }
    }
}

