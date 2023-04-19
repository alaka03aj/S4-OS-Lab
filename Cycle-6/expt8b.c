//implementation memory allocation methods for fixed partition using worst fit.

#include <stdio.h>
#define max 25

void main(){
	int nb, np, max_mem, i, j, index = 0;
	int mem_block[max], size[max], available[max];
	printf("Enter number of memory blocks: ");
	scanf("%d",&nb);
	printf("Enter number of processes: ");
	scanf("%d",&np);
	
	printf("Enter size of memory blocks\n");
	for (i=0; i<nb; i++){
		scanf("%d",&mem_block[i]);
	}
	
	//all memory blocks are available
	for (i=0; i<nb; i++)
		available[i] = 1;
	
	printf("Enter size of processes\n");
	for (i=0; i<np; i++){
		scanf("%d", &size[i]);
	}
	
	for (i=0; i<np; i++){
		max_mem = -1;		//storing index 0 value to max_mem
		j = 0;
		index = 0;
		while (j<nb){
			if (available[j] == 1 && max_mem <= mem_block[j] && mem_block[j]>=size[i]){
				max_mem = mem_block[j];
				index = j;
			}
			j++;
		}
			
		if (available[index] == 1){
				mem_block[index] -= size[i];
				available[index] = 0;
				size[i] = 0;
		}
	}
	
	printf("Memory Block after allocation\n");
	for (i=0; i<nb; i++)
		printf("%d\n", mem_block[i]);
	for (i=0; i<np; i++){
		if (size[i] != 0){
			printf("Process of size %d was not allocated to memory!\n", size[i]);
		}
	}
}
