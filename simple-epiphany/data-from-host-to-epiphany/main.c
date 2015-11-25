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
  e_mem_t emem;           // shared memory buffer
  e_mem_t shared_matrix1;
  e_mem_t shared_matrix2;

  e_init(NULL);
  e_reset_system();
  e_get_platform_info(&platform);

  rows = platform.rows;
  cols = platform.cols;
  ncores = rows * cols;
  float result[ncores];     // to store the results, size of cores

  // allocate a space to share data between e_cores and here
  // offset starts from 0x8e00'0000
  // sdram (share space) is at 0x8f00'0000
  // so 0x8e00'0000 + 0x0100'0000 = 0x8f00'0000
  e_alloc(&emem, BUFOFFSET, ncores*sizeof(float));
  e_alloc(&shared_matrix1, BUFOFFSET + ncores*sizeof(float), 200*sizeof(float));
  e_alloc(&shared_matrix2, BUFOFFSET + ncores*sizeof(float) + 200*sizeof(float), 200*sizeof(float));

  float y[200];
  float x[200];
  for(i=0; i<200; i++) y[i] = x[i] = i;
  int status = e_write(&shared_matrix1, 0, 0, 0x0, y, 200*sizeof(float));
  printf("Status of shared_matrix1 writing: %i\n", status);
  status = e_write(&shared_matrix2, 0, 0, 0x0, x, 200*sizeof(float));
  printf("Status of shared_matrix2 writing: %i\n", status);

  e_open(&dev, 0, 0, rows, cols); // Create an epiphany cores workgroup
  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      e_load("emain.srec", &dev, i, j, E_FALSE);
      e_start(&dev, i, j);
    }
  }

  // we read from the allocated space and store it to result array
  e_read(&emem, 0, 0, 0x0, &result, ncores * sizeof(float)); // reads what's ben put in buffer

  for(i = 0; i < ncores; i++)
    printf("Result from core n°%02i is %f\n",i, result[i]);

  return 0;
}
