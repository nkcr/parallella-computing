#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

unsigned test SECTION(".text_bank3");

volatile unsigned *result;

int main(void) {
  unsigned row, col, delay, num, core_id;

  row = e_group_config.core_row;
  col = e_group_config.core_col;
  core_id = e_get_coreid();
  num = row * e_group_config.group_cols + col;
  result  = (volatile unsigned *) (0x8f100000 + 0x4*num); // writing to external memory, writing 4bytes
  *result = num;
}
