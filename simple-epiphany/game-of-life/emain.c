#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <e-lib.h> // Epiphany cores library

#define READY 0x1
#define DEAD  'O'
#define ALIVE 'X'
/*
 * [0] ready, 0 = not 1 = ready
 * [1] status, O = dead X = alive
 */
char swap[8] SECTION(".text_bank2");
volatile char *result;

int main(void) {
  int i = 0;

  unsigned core_row, core_col,
           group_rows, group_cols,
           delay, core_num, core_id;

  core_row = e_group_config.core_row;
  core_col = e_group_config.core_col;
  group_rows = e_group_config.group_rows;
  group_cols = e_group_config.group_cols;

  core_id = e_get_coreid();
  core_num = core_row * group_cols + core_col;

  unsigned neighbor_row, neighbor_col;
  e_neighbor_id(E_NEXT_CORE, E_GROUP_WRAP, &neighbor_row, &neighbor_col);
  unsigned neighbor_num = neighbor_row * group_cols + neighbor_col;
  unsigned neighbor_id = e_coreid_from_coords(neighbor_row, neighbor_col);

  swap[1] = DEAD;
  swap[0] = READY;

  char neighbor_status;
  do {
    e_read(&e_group_config,&neighbor_status,neighbor_row,neighbor_col,(char*)0x4000,1);
  } while(neighbor_status != READY);

  result  = (volatile char *) (0x8f000000 + 0x1*core_num); // writing to external memory, writing 4bytes

  unsigned alive_neighbor;
  while(1) {
    alive_neighbor = 0;
    if(core_row == 0 && core_col == 0) {
      alive_neighbor += 5; // dead anyway!
    }
    else if(core_row == 0 && core_col == group_cols-1) {
      alive_neighbor += 5; // dead anyway!
    }
    else if(core_row == group_rows-1 && core_col == 0) {
      alive_neighbor += 5; // dead anyway!
    }
    else if(core_row == group_rows-1 && core_col == group_cols-1) {
      alive_neighbor += 5; // dead anyway!
    }
    else if(core_row == 0) {
      alive_neighbor += 3;
      e_read(&e_group_config,&neighbor_status,core_row,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
    }
    else if(core_row == group_rows-1) {
      alive_neighbor += 3;
      e_read(&e_group_config,&neighbor_status,core_row,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
    }
    else if(core_col == 0) {
      alive_neighbor += 3;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
    }
    else if(core_col == group_cols-1) {
      alive_neighbor += 3;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
    } else {
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row-1,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col-1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
      e_read(&e_group_config,&neighbor_status,core_row+1,core_col+1,(char*)0x4001,1);
      if(neighbor_status == ALIVE) alive_neighbor++;
    }
    if(alive_neighbor == 3) swap[1] = ALIVE;
    else if(alive_neighbor < 2) swap[1] = DEAD;
    else if(alive_neighbor > 3) swap[1] = DEAD;
    *result = swap[1];
  }
}
