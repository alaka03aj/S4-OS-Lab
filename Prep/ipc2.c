#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

int main(){
  int i;
  void *shared_mem;
  char buff[100];
  int id = shmget((key_t)2345, 1024, 0666);
  shared_mem = shmat(id, NULL, 0);
  strcpy(buff, (char *)shared_mem);
  if (buff[0] == '1') printf("Yes!");
  else printf("Ayy");
  return 0;
}