#include<stdio.h>
#include<stdlib.h>

#define MAXLINE 150
#define N_NODES 200

typedef struct node {
  int id;
  struct node *next;
} Node;

struct edge {
  int a;
  int b;
  struct edge *next;
};

int run_karger();

int main()
{
  int i, res;
  int min = 100000000;

  for(i=0; i<200; i++) {
    res = run_karger();

    if(res < min)
      min = res;
  }

  printf("Min: %d\n", min);
}

int run_karger()
{
  FILE *fp = fopen("kargerMinCut.txt", "rb");
  char *line = NULL;
  size_t len = 0;
  int id, next_id;
  Node* nodes[N_NODES+1] = { NULL };
  Node* next;
  Node* node_a;
  Node* node_b;
  Node* to_remove;
  int offset, read;
  int i, j;
  int remaining;
  int r_node;
  int count;

  while(getline(&line, &len, fp) != EOF) {
    sscanf(line, "%d%n", &id, &offset);

    /* printf("Populating node %d\n", id); */

    if(nodes[id] == NULL) {
      nodes[id] = malloc(sizeof(struct node));
      nodes[id]->id = id;
      nodes[id]->next = NULL;
    }

    next = nodes[id];

    while(next->next != NULL)
      next = next->next;

    while(sscanf(line+offset, "%d%n", &next_id, &read) == 1) {
      /* printf("\tadding edge to: %d\n", next_id); */

      next->next = malloc(sizeof(Node));
      next = next->next;
      next->id = next_id;
      next->next = NULL;

      offset += read;
    }
  }

  fclose(fp);

  for(remaining=N_NODES; remaining>2; remaining--) {
    r_node = (int)((double)rand() / ((double)RAND_MAX + 1) * remaining) + 1;

    for(j=0; r_node > 0; j++) {
      if(nodes[j+1] != NULL) r_node--;
    }

    node_a = nodes[j];
    node_b = nodes[node_a->next->id];

    /* traverse to end of a's tail */

    next = node_a;
    while(next->next != NULL) {
      next = next->next;
    }
    /* append b's tail onto the end of a */
    next->next = node_b->next;

    /* traverse all nodes, replacing references to b with a */
    for(i=1; i<=N_NODES; i++) {
      if(nodes[i] == NULL) continue;

      next = nodes[i]->next;

      while(next != NULL) {
        if(next->id == node_b->id) {
          next->id = node_a->id;
        }

        next = next->next;
      }
    }

    /* remove self-loops */
    next = node_a;
    while(next->next != NULL) {
      if(next->next->id == node_a->id) {
        to_remove = next->next;
        next->next = to_remove->next;
        free(to_remove);
      }
      else {
        next = next->next;
      }
    }

    /* remove node_b from array and free it */
    nodes[node_b->id] = NULL;
    free(node_b);
  }

  count=0;
  next = node_a->next;
  while(next != NULL) {
    count++;
    next = next->next;
  }

  for(i=1; i<=N_NODES; i++) {
    if(nodes[i] == NULL) continue;

    next = nodes[i]->next;

    while(next != NULL) {
      to_remove = next;
      next = next->next;
      free(to_remove);
    }

    free(nodes[i]);
  }

  return count;
}
