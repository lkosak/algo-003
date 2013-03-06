#include<stdio.h>
#include<stdlib.h>

#define SIZE_T_MAX (size_t)(-1)
#define INITIAL_SIZE 3

typedef struct heap {
  int size;
  int capacity;
  int *arr;
} Heap;

Heap* new_heap();
void heap_insert(Heap* H, int val);
int extract_min(Heap* H);
void heap_free(Heap* H);
