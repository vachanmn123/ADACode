#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void quickSort(int A[], int low, int high);
int partition(int A[], int low, int high);
void swap(int *a, int *b);
void printArray(int A[], int n);
void generateRandomArray(int X[], int n);
double timeQuickSort(int arr[], int n);
void quickSort(int A[], int low, int high)
{
  if (low < high)
  {
    int pi = partition(A, low, high);
    quickSort(A, low, pi - 1);
    quickSort(A, pi + 1, high);
  }
}
int partition(int A[], int low, int high)
{
  int pivot = A[high];
  int i = (low - 1), j;
  for (j = low; j <= high - 1; j++)
  {
    if (A[j] < pivot)
    {
      i++;
      swap(&A[i], &A[j]);
    }
  }
  swap(&A[i + 1], &A[high]);
  return (i + 1);
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
double timeQuickSort(int arr[], int n)
{
  clock_t start, end;
  double time_used;
  start = clock();
  quickSort(arr, 0, n - 1);
  end = clock();
  time_used = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
  return time_used;
}
int main()
{
  FILE *fp;
  fp = fopen("time_vs_n_quick.dat", "w");
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
      totalTime += timeQuickSort(tempArr, n);
      free(tempArr);
    }
    double averageTime = totalTime / num_tests;
    printf("%d\t%.2f\n", n, averageTime);
    fprintf(fp, "%d\t%.2f\n", n, averageTime);
  }
  quickSort(arr, 0, num - 1);
  printf("\nSorted Array:\n");
  printArray(arr, num);
  free(arr);
  fclose(fp);
  printf("Data saved to 'time_vs_n_quick.dat'\n");
  return 0;
}