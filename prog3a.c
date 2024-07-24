#include <stdio.h>
int main(void)
{
  int n, i, j, k;
  int iaFloyd[10][10];
  printf("\n\t PROGRAM TO IMPLEMENT FLOYD'S ALGORITHM \t\n");
  printf("enter the number of vertices \n");
  scanf("%d", &n);
  printf("\n enter the cost adjacency matrix \n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &iaFloyd[i][j]);
  for (k = 0; k < n; k++)
  {
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        if (iaFloyd[i][j] > (iaFloyd[i][k] + iaFloyd[k][j]))
          iaFloyd[i][j] = (iaFloyd[i][k] + iaFloyd[k][j]);
      }
    }
  }
  printf("\n all pair shortest path matrix \n");
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%d\t", iaFloyd[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  return 0;
}
