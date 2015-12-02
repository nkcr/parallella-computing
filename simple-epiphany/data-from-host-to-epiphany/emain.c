#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

volatile float *result;
volatile float *shared_matrix1;
volatile float *shared_matrix2;
// An attempt to use a function pointer, doesn't work
typedef float (*plus_t)(float, float);
volatile plus_t *orders;

int main(void) {
  unsigned row, col, delay, num, core_id;

  row = e_group_config.core_row;
  col = e_group_config.core_col;
  core_id = e_get_coreid();
  num = row * e_group_config.group_cols + col;
  result  = (volatile float *) (0x8f000000 + 0x4*num); // writing to external memory, writing 4bytes
  shared_matrix1 = (volatile float *) (0x8f000000 + 16*sizeof(float));
  shared_matrix2 = (volatile float *) (0x8f000000 + 16*sizeof(float) + 200*sizeof(float));
  orders = (volatile plus_t*) (0x8f000000 + 16*sizeof(float) + 200*sizeof(float) + 200*sizeof(float));

  *result = shared_matrix1[num] + shared_matrix2[num] + num / 10.0;
  //*result = orders[0](1,1); // An attempt to use a function pointer, doesn't work
}
