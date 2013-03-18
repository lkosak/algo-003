#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>

#define SIZE_T_MAX (size_t)(-1)
#define INITIAL_SIZE 100

typedef struct h_node {
  int key;
  int val;
} HNode;

typedef struct heap {
  int size;
  int capacity;
  HNode **arr;
} Heap;

Heap* new_heap();
void heap_insert(Heap* H, int key, int val);
int extract_min(Heap* H, int* key, int* val);
int peek_min(Heap* H, int* key, int* val);
void heap_free(Heap* H);
void print_heap(Heap* H);
int heap_empty(Heap* H);
void heap_decrease_key(Heap* H, int key, int val);

#endif
