#include <stdio.h>
#include <stdlib.h>

#include <e-hal.h>  // Epiphany Hardware Abstraction Layer
                    // functionality for communicating with epiphany chip when
                    // the application runs on a host, typically the ARM µp

#define BUFOFFSET (0x01000000)  // SDRAM is at 0x8f00'0000,
                                // offset in e_read starts at 0x8e00'0000

unsigned rows, cols, i, j, ncores;

/*
 * Init the epiphany platform
 */
void init_epiphany(e_platform_t * platform) {
  e_init(NULL);
  e_reset_system();
  e_get_platform_info(platform);
}

/*
 * Create the workgroup and load programs into it
 */
init_workgroup(e_epiphany_t * dev) {
  e_return_stat_t result;
  e_open(dev, 0, 0, rows, cols); // Create an epiphany cores workgroup
  e_reset_group(dev);
  // load programs into cores workgroup, do not execute it immediately
  result = e_load_group("emain.srec", dev, 0, 0, rows, cols, E_FALSE);
  if(result != E_OK) {
    printf("Error Loading the Epiphany Application %i\n", result);
  }
  e_start_group(dev);
}

/*
 * Main entry
 */
int main(int argc, char * argv[]) {
  e_platform_t platform;  // platform infos
  e_epiphany_t dev;       // provides access to cores workgroup
  e_mem_t emem;           // shared memory buffer

  init_epiphany(&platform);

  rows = platform.rows;
  cols = platform.cols;
  ncores = rows * cols;
  int result[ncores];     // to store the results, size of cores
  // allocate a space to share data between e_cores and here
  // offset starts from 0x8e00'0000
  // sdram (shared space) is at 0x8f00'0000
  // so 0x8e00'0000 + 0x0100'0000 = 0x8f00'0000
  e_alloc(&emem, BUFOFFSET, 4*ncores);

  init_workgroup(&dev);
  usleep(10000);
  // we read from the allocated space and store it to the result array
  e_read(&emem, 0, 0, 0x0, &result, ncores * sizeof(int)); // reads what's ben put in buffer
  e_close(&dev);
  for(i = 0; i < ncores; i++)
    printf("The result is 0x%04x\n", result[i]);

  return 0;
}
