#include "heap.h"

void grow_heap(Heap* H);

Heap* new_heap()
{
  Heap* H = malloc(sizeof(Heap));
  H->size = 0;
  H->capacity = INITIAL_SIZE;
  H->arr = malloc(sizeof(int) * INITIAL_SIZE);

  return H;
}

void heap_insert(Heap *H, int val)
{
  int parent;
  int tmp;
  int pos = H->size;

  /* Make sure the heap has space to hold the new value */
  grow_heap(H);

  H->arr[pos] = val;

  if(pos % 2 == 0)
    parent = (pos+1)/2;
  else
    parent = pos/2;

  /* bubble up */
  while(H->arr[parent] > H->arr[pos]) {
    tmp = H->arr[parent];
    H->arr[parent] = H->arr[pos];
    H->arr[pos] = tmp;

    pos = parent;

    if(pos % 2 == 0)
      parent = (pos+1)/2;
    else
      parent = pos/2;
  }

  H->size++;
}

int extract_min(Heap* H)
{
  int val;
  int tmp;
  int pos, child, l_child, r_child;
  int *arr = H->arr;

  if(H->size > 0) {
    val = arr[0];

    arr[0] = arr[H->size-1];
    H->size--;

    pos = 1;
    child = 0;
    if(pos*2 <= H->size) {
      child = pos*2;
      if(child+1 <= H->size && arr[child] < arr[child-1])
        child++;
    }

    /* bubble down */
    while(child != 0 && arr[pos-1] > arr[child-1]) {
      tmp = arr[child-1];
      arr[child-1] = arr[pos-1];
      arr[pos-1] = tmp;

      pos = child;
      child = 0;
      if(pos*2 <= H->size) {
        child = pos*2;
        if(child+1 <= H->size && arr[child] < arr[child-1])
          child++;
      }
    }

    return val;
  }
  else {
    fputs("Heap empty; can't extract min\n", stderr);
    exit(1);
  }
}

void heap_free(Heap* H)
{
  free(H->arr);
  free(H);
}

void grow_heap(Heap* H)
{
  if(H->size == H->capacity) {
    int new_capacity = H->capacity * 2;

    if(new_capacity < SIZE_T_MAX/sizeof(int)) {
      int *new_array = realloc(H->arr, new_capacity*sizeof(int));

      if(new_array != NULL) {
        H->arr = new_array;
        H->capacity = new_capacity;
      }
      else {
        fputs("Error: out of memory", stderr);
      }
    }
    else {
      fputs("Error: overflow\n", stderr);
    }
  }
}

