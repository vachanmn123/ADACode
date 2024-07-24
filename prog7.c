#include <stdio.h>
#include <stdlib.h>

struct Item
{
  int value;
  int weight;
  double ratio;
};

int compare(const void *a, const void *b)
{
  struct Item *item1 = (struct Item *)a;
  struct Item *item2 = (struct Item *)b;
  double ratio1 = item1->ratio;
  double ratio2 = item2->ratio;
  if (ratio1 > ratio2)
    return -1;
  else if (ratio1 < ratio2)
    return 1;
  else
    return 0;
}

void discreteKnapsack(struct Item items[], int n, int capacity)
{
  int i, j;
  int dp[n + 1][capacity + 1];
  for (i = 0; i <= n; i++)
  {
    for (j = 0; j <= capacity; j++)
    {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (items[i - 1].weight <= j)
        dp[i][j] = (items[i - 1].value + dp[i - 1][j - items[i - 1].weight] > dp[i - 1][j]) ? (items[i - 1].value + dp[i - 1][j - items[i - 1].weight]) : dp[i - 1][j];
      else
        dp[i][j] = dp[i - 1][j];
    }
  }
  printf("Total value obtained for discrete knapsack: %d\n", dp[n][capacity]);
}

void continuousKnapsack(struct Item items[], int n, int capacity)
{
  int i;
  double totalValue = 0.0;
  int remainingCapacity = capacity;
  for (i = 0; i < n; i++)
  {
    if (remainingCapacity >= items[i].weight)
    {
      totalValue += items[i].value;
      remainingCapacity -= items[i].weight;
    }
    else
    {
      totalValue += (double)remainingCapacity / items[i].weight * items[i].value;
      break;
    }
  }
  printf("Total Value obtained for continuous Knapsack: %0.2f\n", totalValue);
}

int main()
{
  int n, capacity, i;
  printf("Enter the number of items: ");
  scanf("%d", &n);
  struct Item items[n];
  printf("Enter the capacity of the knapsack: ");
  scanf("%d", &capacity);
  printf("Enter the value and weight of each item:\n");
  for (i = 0; i < n; i++)
  {
    scanf("%d %d", &items[i].value, &items[i].weight);
    items[i].ratio = (double)items[i].value / items[i].weight;
  }
  qsort(items, n, sizeof(struct Item), compare);
  discreteKnapsack(items, n, capacity);
  continuousKnapsack(items, n, capacity);
  return 0;
}
