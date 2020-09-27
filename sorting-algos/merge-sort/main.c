/* Merge sort */

#include <stdio.h>

#define MAXARRSIZE 65536

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
int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    fprintf(stderr, "error: no input file provided\nUsage: ./program inputfile\n");
    return 1;
  }

  FILE *inputFilePtr = fopen(argv[1], "r");

  if (inputFilePtr == NULL)
  {
    fprintf(stderr, "error: can't open input file %s\n", argv[1]);
    return 2;
  }

  int numOfArrElems;
  int arr[MAXARRSIZE];

  if (fscanf(inputFilePtr, "%d", &numOfArrElems) != 1)
  {
    fprintf(stderr, "error: read failure\n");
    return 3;
  }

  if (numOfArrElems > MAXARRSIZE)
  {
    fprintf(stderr, "error: number of array elements exceeded the limit of %d\n", MAXARRSIZE);
    return 4;
  }

  for (int i = 0, isRead = 0; i < numOfArrElems; ++i)
  {
    if ((isRead = fscanf(inputFilePtr, "%d", &arr[i])) != 1)
    {
      if (isRead == EOF)
      {
        numOfArrElems = i;
        break;
      }
      else
      {
        fprintf(stderr, "error: read failure\n");
        return 3;
      }
    }
  }

  mergeSort(arr, 1, numOfArrElems);

  for (int i = 0; i < numOfArrElems; ++i)
  {
    fprintf(stdout, "%d\n", arr[i]);
  }

  fclose(inputFilePtr);
  return 0;
}
