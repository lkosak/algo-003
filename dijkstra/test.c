#include "dijkstra.h"
#include "heap.h"

void print_heap(Heap* H);

int main()
{
  Heap* H = new_heap();
  int key;
  int val;
  int i;

  for(i=10; i>0; i--) {
    printf("Inserted %d (%d)\n", i, i);
    heap_insert(H, i, i);
  }

  print_heap(H);

  for(i=0; i<10; i++) {
    extract_min(H, &key, &val);
    printf("Extracted key %d with node %d\n", key, val);
  }

  heap_free(H);

  return 0;
}
