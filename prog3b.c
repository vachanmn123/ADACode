#include <stdio.h>
void WarshallTransitiveClosure(int graph[100][100], int numVert);
int main(void)
{
  int i, j, numVert;
  int graph[100][100];
  printf("Warshall's Transitive closure \n");
  printf("enter the number of vertices: ");
  scanf("%d", &numVert);
  printf("enter the adjacency matrix: \n");
  for (i = 0; i < numVert; i++)
    for (j = 0; j < numVert; j++)
      scanf("%d", &graph[i][j]);
  WarshallTransitiveClosure(graph, numVert);
  printf("\n the trasitive closure for the given graph is \n");
  for (i = 0; i < numVert; i++)
  {
    for (j = 0; j < numVert; j++)
    {
      printf("%d\t", graph[i][j]);
    }
    printf("\n");
  }
  return 0;
}
void WarshallTransitiveClosure(int graph[100][100], int numVert)
{
  int i, j, k;
  for (k = 0; k < numVert; k++)
  {
    for (i = 0; i < numVert; i++)
    {
      for (j = 0; j < numVert; j++)
      {
        if (graph[i][j] || (graph[i][k] && graph[k][j]))
          graph[i][j] = 1;
      }
    }
  }
}
