/* Merge sort */

#include <stdio.h>

// Create two subarrays based on `first`, `mid`, `last`
// Then merge those in ascending order into the original array
void mergeArrs(int arr[], int first, int mid, int last)
{
  int leftLen = (mid - first) + 1;
  int rightLen = last - mid;

  int left[leftLen], right[rightLen];

  for (int i = first - 1, j = 0; j < leftLen; ++i, ++j)
  {
    left[j] = arr[i];
  }

  for (int i = mid, j = 0; j < rightLen; ++i, ++j)
  {
    right[j] = arr[i];
  }

  int i = 0, j = 0, k = first - 1;
  int l = k + (last - first) + 1;
  while (k < l)
  {
    if (j >= rightLen || (i < leftLen && left[i] <= right[j]))
    {
      arr[k] = left[i];
      ++i;
    }
    else
    {
      arr[k] = right[j];
      ++j;
    }
    ++k;
  }
}

// Recursively sort the `arr`
void mergeSort(int arr[], int first, int last)
{
  if (last > first)
  {
    int mid = (first + last) / 2;
    mergeSort(arr, first, mid);
    mergeSort(arr, mid + 1, last);
    mergeArrs(arr, first, mid, last);
  }
}

// Main function
int main(void)
{
  int arr1[] = {4, 2, 5, 1, 0, 9};
  int arrLen = sizeof(arr1) / sizeof(arr1[0]);

  printf("Before merge sort: ");
  for (int i = 0; i < arrLen; ++i)
  {
    printf("%d ", arr1[i]);
  }
  printf("\n");

  mergeSort(arr1, 1, arrLen);

  printf("After merge sort: ");
  for (int i = 0; i < arrLen; ++i)
  {
    printf("%d ", arr1[i]);
  }
  printf("\n");

  return 0;
}
