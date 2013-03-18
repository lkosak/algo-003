#include<stdio.h>
#include "../heap.h"

int main(int argc, char *argv[])
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  int val, min;
  Heap* Hlow = new_heap();
  Heap* Hhigh = new_heap();
  int sum = 0;

  if(argv[1] == NULL) {
    printf("Please specify a source file\n");
    exit(1);
  }

  if((fp = fopen(argv[1], "rb")) == NULL) {
    printf("Couldn't open file. Whomp whomp.\n");
    exit(1);
  }

  while(getline(&line, &len, fp) != EOF) {
    sscanf(line, "%d", &val);

    if(Hlow->size > 0) {
      peek_min(Hlow, &min, &min);

      if(0-val < min)
        heap_insert(Hhigh, val, val);
      else
        heap_insert(Hlow, 0-val, 0-val);
    }
    else {
      heap_insert(Hlow, 0-val, 0-val);
    }

    /* Equalize size of heaps */
    if(Hhigh->size > Hlow->size) {
      extract_min(Hhigh, &val, &val);
      heap_insert(Hlow, 0-val, 0-val);
    }
    else if(Hlow->size > Hhigh->size+1) {
      extract_min(Hlow, &val, &val);
      heap_insert(Hhigh, 0-val, 0-val);
    }

    peek_min(Hlow, &min, &min);
    /* printf("Min: %d\n", min); */
    sum += (0-min);
  }

  printf("Res: %d\n", sum%10000);

  return 0;
}
