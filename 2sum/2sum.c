#include<stdio.h>
#include "uthash.h"

struct item {
  int id;
  UT_hash_handle hh;
};


int main(int argc, char *argv[])
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  struct item *number;
  int val;
  struct item *numbers = NULL;
  int i;
  int found = 0;
  int search;
  struct item *result;
  int interval_start = atoi(argv[1]);
  int interval_stop = atoi(argv[2]);

  if(argv[3] == NULL) {
    printf("Please specify a source file\n");
    exit(1);
  }

  if((fp = fopen(argv[3], "rb")) == NULL) {
    printf("Couldn't open file. Whomp whomp.\n");
    exit(1);
  }

  while(getline(&line, &len, fp) != EOF) {
    sscanf(line, "%d", &val);

    if(val <= interval_stop) {
      number = malloc(sizeof(struct item));
      number->id = val;
      HASH_ADD_INT(numbers, id, number);
    }
  }

  for(i=interval_start; i <= interval_stop; i++) {
    for(number=numbers; number != NULL; number=number->hh.next) {
      result = NULL;
      search = i-number->id;

      if(search != number->id) {
        HASH_FIND_INT(numbers, &search, result);

        if(result != NULL) {
          printf("%d + %d  = %d\n", number->id, search, i);
          found++;
          break;
        }
      }
    }
  }

  printf("Found: %d\n", found);

  return 0;
}
