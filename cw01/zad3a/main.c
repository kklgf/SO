#include "libdiff.h"
#include <stdio.h>
#include <sys/times.h>
#ifdef dynamic 
#include <dlfcn.h>
#endif

static struct tms tms_start, tms_end;
static clock_t clock_start, clock_end;

#define time_it(name, code_block)\
  clock_start = times(&tms_start);\
  code_block\
  clock_end = times(&tms_end);\
  printf("\n%s\n", name);\
  printf("real time: %ld\n", clock_end - clock_start);\
  printf(" sys time: %ld\n", tms_end.tms_stime - tms_start.tms_stime);\
  printf("user time: %ld\n", tms_end.tms_utime - tms_start.tms_utime)

int main(int argc, char **argv) {
  #ifdef dynamic
  void* handle = dlopen("./libdiff.so", RTLD_NOW);
  if( !handle ) {
    fprintf(stderr, "dlopen() %s\n", dlerror());
    exit(1);
  }
  table* (*new_table)(int) = dlsym(handle, "new_table");
  void (*compare_seq)(table*, char**) = dlsym(handle, "compare_seq");
  void (*rm_block)(table*, int) = dlsym(handle, "rm_block");
  void (*rm_operation)(table*, int, int) = dlsym(handle, "rm_operation");
  #endif

  table* tbl_main = NULL;

  for (int i = 1; i < argc; i++) {
    char* arg = argv[i];
    if (strcmp(arg, "remove_operation") == 0) {
      int index_blk = atoi(argv[++i]);
      int index_operation = atoi(argv[++i]);
      time_it("remove_operation", {
        rm_operation(tbl_main, index_blk, index_operation);
      });
    }

    else if (strcmp(arg, "remove_block") == 0) {
      int index_blk = atoi(argv[++i]);
      time_it("remove_block", {
        rm_block(tbl_main, index_blk);
      });
    }

    else if (strcmp(arg, "compare_pairs") == 0) {
      time_it("compare_pairs", {
        compare_seq(tbl_main, argv + i + 1);
      });
      i = i + tbl_main->length;
    }

    else if(strcmp(arg, "create_table") == 0) {
      if (tbl_main) free(tbl_main);
      int size = atoi(argv[++i]);
      time_it("create_table", { 
        tbl_main = new_table(size);
      });
    }
  }
  return 0;
}
