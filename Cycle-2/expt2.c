#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void main(){
	DIR *dirp;
	struct dirent *dp;
	char name[100];
	
	printf("Enter directory name: "); //Can by . ./ .. ../../ etc (dir path)
	scanf("%s",name);
	if ((dirp = opendir(name)) == NULL){
		perror("Empty");
		exit(1);
	}
	
	while (dp = readdir(dirp)){
		printf("%s\n",dp->d_name);
	}
	
	closedir(dirp);
}
