#include "heap.h"

void grow_heap(Heap* H);
void heap_bubble_up(Heap* H, int pos);
void heap_bubble_down(Heap* H, int pos);

Heap* new_heap()
{
  Heap* H = malloc(sizeof(Heap));
  H->size = 0;
  H->capacity = INITIAL_SIZE;
  H->arr = malloc(sizeof(HNode*) * INITIAL_SIZE);

  return H;
}

void heap_insert(Heap *H, int key, int val)
{
  int parent;
  int pos = H->size;

  /* Make sure the heap has space to hold the new value */
  grow_heap(H);

  H->arr[pos] = malloc(sizeof(HNode));
  H->arr[pos]->key = key;
  H->arr[pos]->val = val;
  H->size++;

  heap_bubble_up(H, pos);
}

void heap_decrease_key(Heap* H, int key, int val)
{
  int i;
  int valid = 1;

  for(i = 0; i < H->size; i++) {
    if(H->arr[i]->val == val) {
      if(key < H->arr[i]->key) {
        H->arr[i]->key = key;
        heap_bubble_up(H, i);
      }

      break;
    }
  }
}

int extract_min(Heap* H, int* key, int* val)
{
  if(H->size > 0) {
    *key = H->arr[0]->key;
    *val = H->arr[0]->val;

    H->arr[0] = H->arr[H->size-1];
    H->size--;
    heap_bubble_down(H, 0);

    return 1;
  }
  else {
    fputs("Heap empty; can't extract min\n", stderr);
    return 0;
  }
}

int peek_min(Heap* H, int* key, int* val)
{
  if(H->size > 0) {
    *key = H->arr[0]->key;
    *val = H->arr[0]->val;
    return 1;
  }
  else {
    fputs("Heap empty; can't peek min\n", stderr);
    return 0;
  }
}

void heap_bubble_up(Heap* H, int pos)
{
  int parent;
  HNode* tmp;
  HNode** arr = H->arr;

  if(pos % 2 == 0)
    parent = (pos+1)/2;
  else
    parent = pos/2;

  /* bubble up */
  while(arr[parent]->key > arr[pos]->key) {
    tmp = arr[parent];
    arr[parent] = arr[pos];
    arr[pos] = tmp;

    pos = parent;

    if(pos % 2 == 0)
      parent = (pos+1)/2;
    else
      parent = pos/2;
  }
}

void heap_bubble_down(Heap* H, int pos)
{
  int child, l_child, r_child, swap;
  HNode* tmp;
  HNode** arr = H->arr;

  if(pos == 0) {
    l_child = 1;
    r_child = 2;
  }
  else {
    l_child = pos*2;
    r_child = pos*2+1;
  }

  /* bubble down */
  while(1) {
    if(r_child >= H->size) {
      if(l_child >= H->size)
        break;
      else
        swap = l_child;
    }
    else {
      if(arr[l_child]->key < arr[r_child]->key)
        swap = l_child;
      else
        swap = r_child;
    }

    if(arr[pos]->key > arr[swap]->key) {
      tmp = arr[pos];
      arr[pos] = arr[swap];
      arr[swap] = tmp;

      pos = swap;
      l_child = pos*2;
      r_child = pos*2+1;
    }
    else {
      break;
    }
  }
}

void heap_free(Heap* H)
{
  free(H->arr);
  free(H);
}

int heap_empty(Heap* H)
{
  if(H->size > 0)
    return 0;
  else
    return 1;
}

void print_heap(Heap* H)
{
  int i;

  printf("[");
  for(i=0; i<H->size; i++) {
    if(i > 0) printf(", ");

    printf("%d", H->arr[i]->key);
  }
  printf("]\n");
}

void grow_heap(Heap* H)
{
  if(H->size == H->capacity) {
    int new_capacity = H->capacity * 2;

    if(new_capacity < SIZE_T_MAX/sizeof(int)) {
      HNode **new_array = realloc(H->arr, new_capacity*sizeof(HNode*));

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

