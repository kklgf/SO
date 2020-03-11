#include "libdiff.h"

typedef struct node {
  struct node* next;
  char* value;
} node;

// make and push node with operation after pointed node
// "We wish You a Merry Christmas.."
static void push(node*** tail, char* operation) {
  **tail = calloc(sizeof(struct node), 1);
  (**tail)->value = operation;
  *tail = &(**tail)->next;
}

// run diff comand in OS, save to temporary file
// and return pointer to that file 
static FILE* diff_to_FILE(char* file1, char* file2) {
  static const char* pattern = "diff %s %s > /tmp/operations.txt";
  int length = sizeof(pattern) - 4 + strlen(file1) + strlen(file2) + 1;
  char* out = calloc(sizeof(char*), length);
  sprintf(out, pattern, file1, file2);
  system(out);
  free(out);\
  FILE *f = fopen("/tmp/operations.txt", "r");
  return f;
}

// writes operations to list tail
// returns length of that list
static int get_operations(FILE *f, node** tail) {
  //http://www.cplusplus.com/reference/cstdio/fseek/
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char* content = malloc(fsize + 1);
  fread(content, 1, fsize, f);
  content[fsize] = 0;
  fclose(f);
  int count = 0;

  for (int i = 0, operation_start, operation_end; content[i];) {
    operation_start = i;
    do {
      while (content[i] != '\n' && content[i]) i++;
      if (content[i]) i++;
    } while (content[i] && (content[i] == '<' || content[i] == '-' || content[i] == '>' || content[i] == '\\'));
    operation_end = i;

    int operation_len = operation_end - operation_start + 1;
    char* operation = calloc(sizeof(char), operation_len + 1);

    for (int i = operation_start, j = 0; i < operation_end; ++i, ++j)
      operation[j] = content[i];
      
    push(&tail, operation);
    count++;
    } 
  free(content);
  return count;
}

// create new block with proper length
static block* new_block(int length) {
  block* blk = calloc(sizeof(block), 1);
  blk->operations = calloc(sizeof(char*), length);
  blk->length = length;
  return blk;
}

// create new table with proper length
table* new_table(int length) {
  table* tbl = calloc(sizeof(tbl), 1);
  tbl->values = calloc(sizeof(block*), length);
  tbl->length = length;
  return tbl;
}

// compares 2 files and return
// block with list of operations (differences)
block* compare_pair(char* file1, char* file2) {
  FILE *f = diff_to_FILE(file1, file1);

  if (f == NULL) return NULL;
  
  node* operation_list = NULL;
  int operation_count = get_operations(f, &operation_list);

  block* blk = new_block(operation_count);
  struct node* iter = operation_list, *tmp;
  for (int i = 0; i < operation_count; i++) {
    blk->operations[i] = iter->value;
    tmp = iter;
    iter = iter->next;
    free(tmp);
  }
  blk->files[0] = file1;
  blk->files[1] = file2;
  return blk;
}

void compare_seq(table* tbl, char** sequence) {
  static char* files[2];
  int length = tbl->length;
  for (int i = 0; i < length; i++) {
    if (tbl->values[i]) free(tbl->values[i]);
    files[0] = strtok(sequence[i], ":");
    files[1] = strtok(NULL, "");
    tbl->values[i] = compare_pair(files[0], files[1]);
  }
}

int operation_count(table* tbl, int index_blk) {
  if (tbl == NULL || tbl->values == NULL) return -1;
  block* blk = tbl->values[index_blk];
  int count = 0;
  for (int i = 0; i < blk->length; i++)
    if (blk->operations[i]) count++;
  return count;
}

int block_count(table* tbl) {
  if (tbl == NULL || tbl->values == NULL) return -1;
  int count = 0;
  for (int i = 0; i < tbl->length; i++) 
    if (tbl->values[i]) count++;
  return count;
}

void rm_block(table* tbl, int index_blk) {
  if (tbl->values[index_blk] == NULL) return;
  free(tbl->values[index_blk]);
  tbl->values[index_blk] = NULL;
}

void rm_operation(table* table, int index_blk, int index_operation) {
  block* blk = table->values[index_blk];
  if (blk == NULL) return;
  if (blk->operations[index_operation] == NULL) return;
  free(blk->operations[index_operation]);
  blk->operations[index_operation] = 0;
}
