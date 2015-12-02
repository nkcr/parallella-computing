#include <stdio.h>
#include <stdlib.h>

#include <e-hal.h>  // Epiphany Hardware Abstraction Layer
                    // functionality for communicating with epiphany chip when
                    // the application runs on a host, typically the ARM µp

#define BUFOFFSET (0x01000000)  // SDRAM is at 0x8f00'0000,
                                // offset in e_read starts at 0x8e00'0000

unsigned rows, cols, i, j, ncores;


/*
 * Main entry
 */
int main(int argc, char * argv[]) {
  e_platform_t platform;  // platform infos
  e_epiphany_t dev;       // provides access to cores workgroup
  e_mem_t shared_result;           // shared memory buffer

  e_init(NULL);
  e_reset_system();
  e_get_platform_info(&platform);

  rows = platform.rows;
  cols = platform.cols;
  ncores = rows * cols;
  int result[ncores];

  // allocate a space to share data between e_cores and here
  // offset starts from 0x8e00'0000
  // sdram (share space) is at 0x8f00'0000
  // so 0x8e00'0000 + 0x0100'0000 = 0x8f00'0000
  e_alloc(&shared_result, BUFOFFSET, ncores*sizeof(float));

  e_open(&dev, 0, 0, rows, cols); // Create an epiphany cores workgroup
  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      e_load("emain.srec", &dev, i, j, E_FALSE);
      e_start(&dev, i, j);
    }
  }

  // Here we can select which eCore to unlock
  int ok = 1;
  e_write(&dev, 0, 1, 0x4000, &ok, sizeof(int));
  e_write(&dev, 0, 2, 0x4000, &ok, sizeof(int));

  usleep(2000);

  // we read from the allocated space and store it to result array
  e_read(&shared_result, 0, 0, 0x0, &result, ncores * sizeof(int)); // reads what's ben put in buffer

  for(i = 0; i < ncores; i++)
    printf("Result from core n°%02i is 0x%04x\n",i, result[i]);

  return 0;
}
