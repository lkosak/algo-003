#include "heap.h"

void print_heap(Heap* H);

int main()
{
  int i;
  Heap* H = new_heap();

  heap_insert(H, 3);
  heap_insert(H, 9);
  heap_insert(H, 6);
  heap_insert(H, 5);
  heap_insert(H, 4);
  heap_insert(H, 2);
  heap_insert(H, 1);

  print_heap(H);

  for(i=0; i<7; i++) {
    printf("Extracted: %d\n", extract_min(H));
  }

  heap_free(H);
}

void print_heap(Heap* H)
{
  int i;

  printf("[");
  for(i=0; i<H->size; i++) {
    if(i > 0) printf(", ");

    printf("%d", H->arr[i]);
  }
  printf("]\n");
}
