#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include "kosaraju.h"

typedef struct s_node {
  struct node *data;
  struct s_node *next;
} Stack;

void push(Stack **head, struct node *val);
struct node* pop(Stack **head);
struct node* peek(Stack **head);
int empty(Stack **head);

#endif
