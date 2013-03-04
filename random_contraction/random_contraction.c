#include<stdio.h>
#include<stdlib.h>

#define LINES 200
#define COLUMNS 24

typedef struct vertex {
  int id;
  struct vertex *next;
} Vertex;

struct edge {
  struct vertex *a;
  struct vertex *b;
};

Vertex* get_vertex(struct vertex* vertices[], int id);

int main()
{
  Vertex* vertices[LINES];
  Vertex* vertex;
  int id;
  int i, j;
  char line[1000];

  for(i=0; i<LINES; i++) {
    scanf("%d", &id);

    vertex = get_vertex(vertices, id);

    Vertex *next = vertex;
    while(next->next != NULL)
      next = next->next;

    vertex = get_vertex(vertices, id);
    next->next = vertex;
    next = vertex;
  }
}

Vertex* get_vertex(struct vertex* vertices[], int id)
{
  if(vertices[id] == NULL) {
    vertices[id] = (Vertex *)malloc(sizeof(Vertex));
    vertices[id]->id = id;
    vertices[id]->next = NULL;
  }

  return vertices[id];
}
