#include<stdio.h>

void quicksort(int arr[], int left, int right, int *comparisons);
int choose_pivot(int arr[], int left, int right);
int partition(int arr[], int left, int right, int pivot_index);
void swap(int arr[], int first, int second);

int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1], "rb");

  char line[128];
  int arr[10000];
  int comparisons = 0;
  int i = 0;
  int len;

  while(fgets(line, sizeof(line), fp)) {
    sscanf(line, "%d", &arr[i]);
    i++;
  }

  len = i;

  quicksort(arr, 0, len-1, &comparisons);

  printf("Result: ");
  for(i = 0; i < len; i++) {
    printf("%d\n", arr[i]);
  }

  printf("Total comparisons: %d\n", comparisons);
}

void quicksort(int arr[], int left, int right, int *comparisons)
{
  int pivot_index, new_pivot_index;

  if(left < right) {
    *comparisons += (right-left);

    pivot_index = choose_pivot(arr, left, right);
    new_pivot_index = partition(arr, left, right, pivot_index);
    quicksort(arr, left, new_pivot_index-1, &*comparisons);
    quicksort(arr, new_pivot_index+1, right, &*comparisons);
  }
}

int choose_pivot(int arr[], int left, int right)
{
  int median;
  median = left + (((right-left+1+1)/2)-1);

  if(arr[left] > arr[median]) {
    if(arr[median] > arr[right])
      return median;
    else if(arr[left] > arr[right])
      return right;
    else
      return left;
  }
  else {
    if(arr[left] > arr[right])
      return left;
    else if(arr[median] > arr[right])
      return right;
    else
      return median;
  }
}

int partition(int arr[], int left, int right, int pivot_index)
{
  int pivot, i, j;

  if(left != pivot_index)
    swap(arr, left, pivot_index);

  pivot = arr[left];
  i = left+1;

  for(j=left+1; j <= right; j++) {
    if(arr[j] < pivot) {
      swap(arr, i, j);
      i++;
    }
  }

  swap(arr, left, i-1);
  return i-1;
}

void swap(int arr[], int first, int second)
{
  int temp;

  temp = arr[first];
  arr[first] = arr[second];
  arr[second] = temp;
}
