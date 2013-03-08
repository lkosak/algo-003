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

  /* int paths[4] = {1,2,3,4}; */
  /* for(i=0; i<4; i++) { */
  /*   printf("Path size for %d: %d\n", paths[i], results[paths[i]]); */
  /* } */

  fclose(fp);
  free(G);
  return 0;
}

int* dijkstra(Node **G, int size, int v)
{
  Heap* H = new_heap();
  Node* next;
  int* A = malloc(sizeof(int) * size+1);
  int i, key;
  int w;

  heap_insert(H, 0, v);

  for(i=2; i<= size; i++) {
    heap_insert(H, 1000000, i);
  }

  while(!heap_empty(H)) {
    extract_min(H, &key, &w);

    A[w] = key;

    /* Look at all the subject's edges */
    next = G[w]->next;
    while(next != NULL) {
      heap_decrease_key(H, key+next->length, next->label);
      next = next->next;
    }
  }

  heap_free(H);

  return A;
}
