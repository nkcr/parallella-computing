#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

#define UNLOCKED (1)
volatile int *result;
volatile int instructions[8] SECTION(".text_bank2"); // 0x4000

int main(void) {
  unsigned row, col, delay, num, core_id;

  row = e_group_config.core_row;
  col = e_group_config.core_col;
  core_id = e_get_coreid();
  num = row * e_group_config.group_cols + col;
  result  = (volatile int *) (0x8f000000 + 0x4*num); // writing to external memory, writing 4bytes

  //instructions[0] = UNLOCKED;
  *result = 0;

  while(1) {
    while(instructions[0] != UNLOCKED);
    *result = num;
  }
}
