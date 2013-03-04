#include "stack.h"

void push(Stack **head, struct node *val)
{
  Stack *node = malloc(sizeof(Stack));

  if(node == NULL) {
    fputs("Cannot add to node\n", stderr);
    abort();
  }
  else {
    node->data = val;
    node->next = empty(head) ? NULL : *head;
    *head = node;
  }
}

struct node* pop(Stack **head)
{
  if(empty(head)) {
    fputs("Error: stack underflow\n", stderr);
    abort();
  }
  else {
    Stack *top = *head;
    struct node *value = top->data;
    *head = top->next;
    free(top);
    return value;
  }
}

struct node* peek(Stack **head)
{
  Stack *top = *head;
  struct node *value = top->data;
  return value;
}

int empty(Stack **head)
{
  return *head == NULL ? 1 : 0;
}
