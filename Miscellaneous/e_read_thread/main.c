#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <e-hal.h>

#define BUFOFFSET (0x01000000)
#define THREAD_NUMBER 20
#define SHARED_BUFFER_SIZE 20

pthread_t tid[THREAD_NUMBER];
long data;
long result = 20;
e_mem_t shared_buffer;

void* thread_function(void * arg) {
  int n = 0;
  while(1) {
    printf("Iteration: %i\n", n++);
    long temp;
    //memcpy(&data,&temp,sizeof(long));
    e_read(&shared_buffer, 0, 0, 0x0, &temp, sizeof(long));
  }
}

int main(void) {
  e_platform_t platform;

  e_init(NULL);
  e_reset_system();
  e_get_platform_info(&platform);
  e_alloc(&shared_buffer, BUFOFFSET, SHARED_BUFFER_SIZE * sizeof(long));

  int err;
  int i = 0;
  for(i = 0; i < THREAD_NUMBER; i++) {
    err = pthread_create(&(tid[i]), NULL, &thread_function, NULL);
    if(err != 0) printf("\nCan't create thread :[%s]", strerror(err));
  }
  while(1);
  return 0;
}
