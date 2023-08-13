#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main(){
  int i;
  char buff[100];
  void *shared_mem;
  int shmid = shmget((key_t)2345, 1024, 0666|IPC_CREAT);
  shared_mem = shmat(shmid, NULL, 0);
  read(0,buff,100);
  strcpy(shared_mem, buff);
  printf("Attached: %s", (char *)shared_mem);
}