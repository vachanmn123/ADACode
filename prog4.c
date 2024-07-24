#include <stdio.h>
#define INFINITY 9999
#define MAX 10
void dijikstra(int cost[10][10], int n, int start)
{
  int distance[10], count, mindist, next, i, j;
  int visited[10], path[10];
  for (i = 0; i < n; i++)
  {
    distance[i] = cost[start][i];
    path[i] = start;
    visited[i] = 0;
  }
  distance[start] = 0;
  visited[start] = 1;
  count = 1;
  while (count < n - 1)
  {
    mindist = INFINITY;
    for (i = 0; i < n; i++)
      if (distance[i] < mindist && !visited[i])
      {
        mindist = distance[i];
        next = i;
      }
    visited[next] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindist + cost[next][i] < distance[i])
        {
          distance[i] = mindist + cost[next][i];
          path[i] = next;
        }
    count++;
  }
  for (i = 0; i < n; i++)
    if (i != start)
    {
      printf("\nDistance of %d = %d", i, distance[i]);
      printf("\nPath = %d", i);
      j = i;
      do
      {
        j = path[j];
        printf("<--%d", j);
      } while (j != start);
    }
}

void main()
{
  int G[MAX][MAX], i, j, n, u;
  printf("\nEnter the number of vertices: ");
  scanf("%d", &n);
  printf("\nEnter the adjacency matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
      scanf("%d", &G[i][j]);
      if (G[i][j] == 0)
        G[i][j] = INFINITY;
    }
  printf("\nEnter the starting node: ");
  scanf("%d", &u);
  dijikstra(G, n, u);
}
