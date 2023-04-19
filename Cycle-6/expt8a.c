//implementation memory allocation methods for fixed partition using first fit.

#include <stdio.h>
#define max 25

void main(){
	int nb, np;
	int mem_block[max], size[max], available[max];
	printf("Enter number of memory blocks: ");
	scanf("%d",&nb);
	printf("Enter number of processes: ");
	scanf("%d",&np);
	
	printf("Enter size of memory blocks\n");
	for (int i=0; i<nb; i++){
		scanf("%d",&mem_block[i]);
	}
	
	for (int i=0; i<nb; i++)
		available[i] = 1;
	
	printf("Enter size of processes\n");
	for (int i=0; i<np; i++){
		scanf("%d", &size[i]);
	}
	
	for (int i=0; i<np; i++){
		for (int j=0; j<nb; j++){
			if (mem_block[j] >= size[i] && available[j]!=0){
				mem_block[j] -= size[i];
				available[j] = 0;
				size[i] = 0;
				break;
			}
		}
	}
	
	printf("Memory Block after allocation\n");
	for (int i=0; i<nb; i++)
		printf("%d\n", mem_block[i]);
	for (int i=0; i<np; i++){
		if (size[i] != 0){
			printf("Process of size %d was not allocated to memory!\n", size[i]);
		}
	}
}
