#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define THREAD_NUMBER 20

pthread_t tid[THREAD_NUMBER];
long data;
long result = 20;

void* thread_function(void * arg) {
  while(1) {
    printf("Iteration\n");
    long temp = result;
    memcpy(&data,&temp,sizeof(long));
  }
}

int main(void) {
  int err;
  int i = 0;
  for(i = 0; i < THREAD_NUMBER; i++) {
    err = pthread_create(&(tid[i]), NULL, &thread_function, NULL);
    if(err != 0) printf("\nCan't create thread :[%s]", strerror(err));
  }
  while(1);
  return 0;
}
