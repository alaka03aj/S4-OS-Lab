//C Program to Simulate the ls Command in Linux Operating system

#include <stdio.h>
#include <dirent.h>

void main(){
	char dirname[10];
	DIR *dirp;
	struct dirent *d;
	printf("Enter directory name: ");
	scanf("%s",dirname);
	dirp = opendir(dirname);
	if (dirp == NULL){
		perror("Cannot find directory");
		exit(-1);
	}
	while (d = readdir(dirp)){
		printf("%s\n",d->d_name);		//displays files in the directory
	}
}
