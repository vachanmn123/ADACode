#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void mergeSort(int A[], int low, int high);
void merge(int A[], int low, int mid, int high);
void swap(int *a, int *b);
void printArray(int A[], int n);
void generateRandomArray(int X[], int n);
double timeMergeSort(int arr[], int n);

void mergeSort(int A[], int low, int high)
{
  if (low < high)
  {
    int mid = low + (high - low) / 2;
    mergeSort(A, low, mid);
    mergeSort(A, mid + 1, high);
    merge(A, low, mid, high);
  }
}
void merge(int A[], int low, int mid, int high)
{
  int n1 = mid - low + 1;
  int n2 = high - mid;
  int i, j;
  int L[n1], R[n2];
  for (i = 0; i < n1; i++)
  {
    L[i] = A[low + i];
  }
  for (j = 0; j < n2; j++)
  {
    R[j] = A[mid + 1 + j];
  }
  i = 0, j = 0;
  int k = low;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      A[k] = L[i];
      i++;
    }
    else
    {
      A[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1)
  {
    A[k] = L[i];
    i++;
    k++;
  }
  while (j < n2)
  {
    A[k] = R[j];
    j++;
    k++;
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
double timeMergeSort(int arr[], int n)
{
  clock_t start, end;
  double time_used;
  start = clock();
  mergeSort(arr, 0, n - 1);
  end = clock();
  time_used = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
  return time_used;
}
int main()
{
  FILE *fp;
  fp = fopen("time_vs_n_merge.dat", "w");
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
  printf("\nGENERATING DATA......\n");
  for (n = 5000; n <= 150000; n += 500)
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
      totalTime += timeMergeSort(tempArr, n);
      free(tempArr);
    }
    double averageTime = totalTime / num_tests;
    fprintf(fp, "%d\t%.2f\n", n, averageTime);
  }
  mergeSort(arr, 0, num - 1);
  printf("\nSorted Array:\n");
  printArray(arr, num);
  free(arr);
  fclose(fp);
  printf("Data saved to 'time_vs_n_merge.dat'\n");
  return 0;
}