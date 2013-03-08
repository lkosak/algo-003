#include "dijkstra.h"

int* dijkstra(Node **G, int size, int v);

int main(int argc, char *argv[])
{
  Node **G = malloc((N_VERTICES+1) * sizeof(Node *));
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  int i, label, adjacent, length, read;
  int offset = 0;
  Node *next;

  if(argv[1] == NULL) {
    printf("Please specify a source file\n");
    exit(1);
  }

  if((fp = fopen(argv[1], "rb")) == NULL) {
    printf("Couldn't open file. Whomp whomp.\n");
    exit(1);
  }

  /* Loop each line, loading in adjacent edges */
  while(getline(&line, &len, fp) != EOF) {
    sscanf(line, "%d%n", &label, &offset);

    if(G[label] == NULL) {
      G[label] = (Node *)malloc(sizeof(Node));
      G[label]->label = label;
      G[label]->explored = 0;
      G[label]->next = NULL;
    }

    next = G[label];
    while(next->next != NULL)
      next = next->next;

    while(sscanf(line+offset, "%d,%d%n", &adjacent, &length, &read) == 2) {
      next->next = (Node *)malloc(sizeof(Node));
      next = next->next;
      next->label = adjacent;
      next->length = length;
      next->next = NULL;

      offset += read;
    }
  }

  int* results = dijkstra(G, N_VERTICES, 1);

  int paths[10] = {7,37,59,82,99,115,133,165,188,197};
  for(i=0; i<10; i++) {
    printf("%d", results[paths[i]]);
    if(i+1 < 10) printf(",");
    /* printf("Path size for %d: %d\n", paths[i], results[paths[i]]); */
  }

  /* int paths[5] = {1,2,3,4,5}; */
  /* for(i=0; i<5; i++) { */
  /*   printf("Path size for %d: %d\n", paths[i], results[paths[i]]); */
  /* } */

  fclose(fp);
  free(G);
  return 0;
}

int* dijkstra(Node **G, int size, int v)
{
  Node* next;
  Node* nearest_tail;
  Node* nearest_head;
  int* A = malloc(sizeof(int) * size+1);
  int i, key;
  int w;

  G[v]->explored = 1;
  A[v] = 0;

  while(1) {
    nearest_tail = NULL;
    nearest_head = NULL;

    for(i=1; i<=size; i++) {
      if(G[i]->explored) {
        /* scan all edges for the given node */
        next = G[i]->next;

        while(next != NULL) {
          if(!G[next->label]->explored) {
            if(nearest_head == NULL
                || A[i]+next->length < A[nearest_tail->label]+nearest_head->length) {
              nearest_tail = G[i];
              nearest_head = next;
            }
          }

          next = next->next;
        }
      }
    }

    if(nearest_head != NULL) {
      G[nearest_head->label]->explored = 1;
      A[nearest_head->label] = A[nearest_tail->label]+nearest_head->length;
    } else {
      /* can't find any more edges */
      break;
    }
  }

  for(i=1; i<=size; i++) {
    if(!G[i]->explored)
      A[i] = 1000000;
  }

  return A;
}
