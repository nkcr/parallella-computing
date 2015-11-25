#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

unsigned test SECTION(".text_bank3");

volatile float *result;
volatile float *shared_matrix1;
volatile float *shared_matrix2;

int main(void) {
  unsigned row, col, delay, num, core_id;

  row = e_group_config.core_row;
  col = e_group_config.core_col;
  core_id = e_get_coreid();
  num = row * e_group_config.group_cols + col;
  result  = (volatile float *) (0x8f000000 + 0x4*num); // writing to external memory, writing 4bytes
  shared_matrix1 = (volatile float *) (0x8f000000 + 16*sizeof(float));
  shared_matrix2 = (volatile float *) (0x8f000000 + 16*sizeof(float) + 200*sizeof(float));
  *result = shared_matrix1[num] + shared_matrix2[num] + num / 10.0;
}
