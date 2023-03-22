#include <stdio.h>
#include <dirent.h>							//library that facilitates directory traversing
#include <stdlib.h>

void main(){
	DIR *dirp;								//DIR is directory stream
	struct dirent *dp;						//creates a pointer to structure??
	char name[100];
	
	printf("Enter directory name: "); 		//Can by . ./ .. ../../ etc (dir path)
	scanf("%s",name);
	if ((dirp = opendir(name)) == NULL){	//opens directory file and mallocs one struct dirent
		perror("Empty");					//if empty, raises error
		exit(1);							//exits
	}
	
	while (dp = readdir(dirp)){				//reads the next directory into one struct dirent and returns a pointer to it
		printf("%s\n",dp->d_name);			//d_name is the file name inside directory
	}
	
	closedir(dirp);							//closes directory file and frees the struct dirent
}
