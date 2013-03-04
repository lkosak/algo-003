#ifndef KOSARAJU_H_INCLUDED
#define KOSARAJU_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

#define N_VERTICES 875714

typedef struct node
{
  int label;
  struct node *next;
  struct node *r_next;
  struct node *leader;
  int explored;
  int f;
} Node;

void dfs_loop(Node *G_sort[], Node *G[], int size, int reverse);
void dfs(Node *G[], Node *i, int reverse);
int node_cmp(const void *a, const void *b);
int int_cmp(const void *a, const void *b);

#endif
