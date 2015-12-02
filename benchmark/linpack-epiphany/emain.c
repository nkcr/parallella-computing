#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

#define LOCKED (0)
#define UNLOCKED (1)

// [0] unlock
// int instructions[8] SECTION(".text_bank2");
struct Instructions {
  int i;
  int j;
  int ldm;
} instructions SECTION(".text_bank2");

volatile float *result;
volatile float *sharedx;
volatile float *sharedy;
volatile float *sharedm;
volatile int *shared_status;

int main(void) {
  unsigned row, col, delay, num, core_id;

  row = e_group_config.core_row;
  col = e_group_config.core_col;
  core_id = e_get_coreid();
  num = row * e_group_config.group_cols + col;
  result  = (volatile float *) (0x8f000000 + 0x4*num); // writing to external memory, writing 4bytes
  sharedx = (volatile float *) (0x8f000000 + 16*sizeof(float));
  sharedy = (volatile float *) (0x8f000000 + 16*sizeof(float) + 200*sizeof(float));
  sharedm = (volatile float *) (0x8f000000 + 16*sizeof(float) + 200*sizeof(float) + 200*sizeof(float));
  shared_status = (volatile int *) (0x8f000000 + 16*sizeof(float) + 200*sizeof(float) + 200*sizeof(float) + 200*201*sizeof(float) + 0x4*num);
  *shared_status = LOCKED;
  while(1) {
    // Read current status, locked?
    while(*shared_status == LOCKED);
    // Compute given instructions
    int i = instructions.i;
    int j = instructions.j;
    int ldm = instructions.ldm;
    sharedy[i] = ((((((((((((((( (sharedy[i])
            + sharedx[j-15]*sharedm[ldm*(j-15)+i])
      + sharedx[j-14]*sharedm[ldm*(j-14)+i])
            + sharedx[j-13]*sharedm[ldm*(j-13)+i])
      + sharedx[j-12]*sharedm[ldm*(j-12)+i])
            + sharedx[j-11]*sharedm[ldm*(j-11)+i])
      + sharedx[j-10]*sharedm[ldm*(j-10)+i])
            + sharedx[j- 9]*sharedm[ldm*(j- 9)+i])
      + sharedx[j- 8]*sharedm[ldm*(j- 8)+i])
            + sharedx[j- 7]*sharedm[ldm*(j- 7)+i])
      + sharedx[j- 6]*sharedm[ldm*(j- 6)+i])
            + sharedx[j- 5]*sharedm[ldm*(j- 5)+i])
      + sharedx[j- 4]*sharedm[ldm*(j- 4)+i])
            + sharedx[j- 3]*sharedm[ldm*(j- 3)+i])
      + sharedx[j- 2]*sharedm[ldm*(j- 2)+i])
            + sharedx[j- 1]*sharedm[ldm*(j- 1)+i])
      + sharedx[j]   *sharedm[ldm*j+i];

    // *result = sharedy[i];
    // Set status to locked
    *shared_status = LOCKED;
  }
}
