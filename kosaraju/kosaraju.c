#include "kosaraju.h"

int t = 0;
struct node *s;

int main(int argc, char *argv[])
{
  Node **G = malloc(N_VERTICES * sizeof(Node *));
  Node **G_sort = malloc(N_VERTICES * sizeof(Node *));
  int *sizes = malloc(N_VERTICES * sizeof(int));
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  int i;
  int tail, head;
  Node *next;

  if(argv[1] == NULL) {
    printf("Please specify a source file\n");
    exit(1);
  }

  if((fp = fopen(argv[1], "rb")) == NULL) {
    printf("Couldn't open file. Whomp whomp.\n");
    exit(1);
  }

  for(i=1; i<=N_VERTICES; i++) {
    G[i] = (Node *)malloc(sizeof(Node));
    G[i]->label = i;
    G[i]->next = NULL;
    G[i]->r_next = NULL;
    G[i]->leader = NULL;
    G[i]->explored = 0;
    G[i]->f = 0;

    G_sort[i] = G[i];
  }

  while(getline(&line, &len, fp) != EOF) {
    sscanf(line, "%d %d", &tail, &head);

    /* add head to tail */
    next = G[tail];
    while(next->next != NULL)
      next = next->next;

    next->next = (Node *)malloc(sizeof(Node));
    next = next->next;
    next->label = head;
    next->next = NULL;

    /* add tail to head for reverse graph */
    next = G[head];
    while(next->r_next != NULL)
      next = next->r_next;

    next->r_next = (Node *)malloc(sizeof(Node));
    next = next->r_next;
    next->label = tail;
    next->r_next = NULL;
  }

  fclose(fp);

  dfs_loop(G_sort, G, N_VERTICES, 1);
  qsort(G_sort+1, N_VERTICES, sizeof(Node *), node_cmp);
  for(i=1; i<=N_VERTICES; i++) G[i]->explored = 0;
  dfs_loop(G_sort, G, N_VERTICES, 0);

  /* calculate and print sizes */
  for(i=1; i<=N_VERTICES; i++) {
    sizes[G[i]->leader->label]++;
  }
  qsort(sizes+1, N_VERTICES, sizeof(int), int_cmp);
  for(i=1; i<=5; i++) {
    printf("#%d - %d\n", i, sizes[i]);
  }

  free(G);
  free(G_sort);
  free(sizes);

  return 0;
}

void dfs_loop(Node *G_sort[], Node *G[], int size, int reverse)
{
  int i;
  t = 0;

  for(i=size; i>=1; i--) {
    if(!G_sort[i]->explored) {
      s = G_sort[i];
      dfs(G, G_sort[i], reverse);
    }
  }
}

void dfs(Node *G[], Node *i, int reverse)
{
  Node *node;
  Node *next;
  Stack *stack = NULL;
  int added;

  push(&stack, i);

  while(!empty(&stack)) {
    node = peek(&stack);

    if(node->explored) {
      if(node->f == 0) {
        t++;
        node->f = t;
      }

      pop(&stack);
    }
    else {
      node->explored = 1;
      node->leader = s;

      added = 0;

      next = reverse ? node->r_next : node->next;

      while(next != NULL) {
        if(!G[next->label]->explored) {
          push(&stack, G[next->label]);
          added++;
        }

        next = reverse ? next->r_next : next->next;
      }

      if(added == 0) {
        t++;
        node->f = t;
        pop(&stack);
      }
    }
  }
}

int node_cmp(const void *a, const void *b)
{
  const struct node **ia = (const struct node**)a;
  const struct node **ib = (const struct node**)b;

  return ((*ia)->f - (*ib)->f);
}

int int_cmp(const void *a, const void *b)
{
  const int *ia = (const int *)a;
  const int *ib = (const int *)b;
  return *ib  - *ia;
}
