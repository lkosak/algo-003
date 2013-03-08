#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include "heap.h"

#define N_VERTICES 200

typedef struct node
{
  int label;
  struct node *next;
  int length;
  int explored;
} Node;

#endif
