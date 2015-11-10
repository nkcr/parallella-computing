#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

#define READY 0x1
char swap[8] SECTION(".text_bank2"); // 32 words
volatile unsigned *result;

int main(void) {
  int i = 0;

  unsigned core_row, core_col,
           group_rows, group_cols,
           delay, core_num, core_id;

  // Retrieving infos about the eCore
  core_row = e_group_config.core_row;
  core_col = e_group_config.core_col;
  group_rows = e_group_config.group_rows;
  group_cols = e_group_config.group_cols;

  core_id = e_get_coreid();
  core_num = core_row * group_cols + core_col;

  // Setting my number to my local bank
  swap[0] = core_num;

  // Retrieving my neighbor
  unsigned neighbor_row, neighbor_col;
  e_neighbor_id(E_NEXT_CORE, E_GROUP_WRAP, &neighbor_row, &neighbor_col);
  unsigned neighbor_num = neighbor_row * group_cols + neighbor_col;
  unsigned neighbor_id = e_coreid_from_coords(neighbor_row, neighbor_col);

  // Setting my ready bit
  swap[1] = READY;

  // Waiting for my neighbor
  char neighbor_status;
  do {
    e_read(&e_group_config,&neighbor_status,neighbor_row,neighbor_col,(char*)0x4001,1);
  } while(neighbor_status != READY);
  e_read(&e_group_config,&neighbor_status,neighbor_row,neighbor_col,(char*)0x4000,1);

  // Reading my neighbor number
  result  = (volatile unsigned *) (0x8f000000 + 0x4*core_num); // writing to external memory, writing 4bytes
  *result = neighbor_status;
}
