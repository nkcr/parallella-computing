#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

#define EFREE (0)
#define EBUSY (1)

struct Instructions {
  int i;
} instructions SECTION(".text_bank2");

volatile float *result;
volatile float *shareddy;
volatile float *sharedda;
volatile float *shareddx;
volatile int   *shared_status;

int main(void) {
  unsigned row, col, num, core_id;

  row = e_group_config.core_row;
  col = e_group_config.core_col;
  core_id = e_get_coreid();
  num = row * e_group_config.group_cols + col;

  result   = (volatile float *) (0x8f000000 + 0x4*num); // writing to external memory, writing 4bytes
  shareddy = (volatile float *) (0x8f000000 + 16*sizeof(float));
  sharedda = (volatile float *) (0x8f000000 + 16*sizeof(float) + 100*sizeof(float));
  shareddx = (volatile float *) (0x8f000000 + 16*sizeof(float) + 100*sizeof(float) + sizeof(float));
  shared_status = (volatile int *) (0x8f000000 + 16*sizeof(float) + 100*sizeof(float) + sizeof(float) + 100*sizeof(float) + 0x4*num);
  *shared_status = EFREE;
  while(1) {
    // Read current status, locked?
    while(*shared_status == EFREE);
    // Compute given instructions
    int i = instructions.i;

    shareddy[i] = shareddy[i] + (*sharedda) * shareddx[i];
    // e_wait(E_CTIMER_0, 900000);
    // *result = sharedy[i];
    // Set status to locked
    *shared_status = EFREE;
  }
}
