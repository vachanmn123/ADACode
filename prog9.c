#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void selectionSort(int A[], int n);
void swap(int *a, int *b);
void printArray(int A[], int n);
void generateRandomArray(int X[], int n);
double timeSelectionSort(int arr[], int n);
void selectionSort(int A[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
  {
    int min_idx = i;
    for (j = i + 1; j < n; j++)
    {
      if (A[j] < A[min_idx])
      {
        min_idx = j;
      }
    }
    if (min_idx != i)
    {
      swap(&A[i], &A[min_idx]);
    }
  }
}
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void printArray(int A[], int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    printf("%d\n", A[i]);
  }
  printf("\n");
}
void generateRandomArray(int X[], int n)
{
  srand(time(NULL));
  int i;
  for (i = 0; i < n; i++)
  {
    X[i] = rand() % 10000;
  }
}
double timeSelectionSort(int arr[], int n)
{
  clock_t start = clock();
  selectionSort(arr, n);
  clock_t end = clock();
  double elapsedTime = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
  return elapsedTime;
}
int main()
{
  FILE *fp;
  fp = fopen("time_vs_n.dat", "w");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
  int num, n, i;
  printf("Enter the number of elements to sort: ");
  scanf("%d", &num);
  int *arr = (int *)malloc(num * sizeof(int));
  if (arr == NULL)
  {
    perror("Memory allocation failed");
    return 1;
  }
  generateRandomArray(arr, num);
  printf("Unsorted array:\n");
  printArray(arr, num);
  printf("n\tTime (ms)\n");
  for (n = 5000; n <= 15000; n += 1000)
  {
    double totalTime = 0.0;
    int num_tests = 5;
    for (i = 0; i < num_tests; i++)
    {
      int *tempArr = (int *)malloc(n * sizeof(int));
      if (tempArr == NULL)
      {
        perror("Memory allocation failed");
        return 1;
      }
      memcpy(tempArr, arr, num * sizeof(int));
      totalTime += timeSelectionSort(tempArr, n);
      free(tempArr);
    }
    double averageTime = totalTime / num_tests;
    printf("%d\t%.2f\n", n, averageTime);
    fprintf(fp, "%d\t%.2f\n", n, averageTime);
  }
  selectionSort(arr, num);
  printf("\nSorted Array:\n");
  printArray(arr, num);
  free(arr);
  fclose(fp);
  printf("Data saved to 'time_vs_n.dat'\n");
  return 0;
}