#ifndef libdiff
#define libdiff

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct block {
  unsigned int length;
  char* files[2];
  char** operations;
} block;

typedef struct table {
  unsigned int length;
  block** values;
} table;

table* new_table(int size);
block* compare_pair(char* file1, char* file2);

void compare_seq(table* table, char** file_sequence);
int operation_count(table* table, int block_index);
int block_count(table* table);
void rm_block(table* table, int block_index);
void rm_operation(table* table, int block_index, int operation_index);

#endif
