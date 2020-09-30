#include <stdio.h>

#define MAXARRSIZE 65536

// Merge two subarrays while calculating inversions in them
int mergeAndCalculate(int arr[], int first, int mid, int last)
{
  int inversions = 0;
  int leftArrLen = (mid - first) + 1, rightArrLen = last - mid;
  int leftArr[leftArrLen], rightArr[rightArrLen];

  int k = first;

  for (int i = 0; i < leftArrLen; ++i, ++k)
  {
    leftArr[i] = arr[k];
  }

  for (int i = 0; i < rightArrLen; ++i, ++k)
  {
    rightArr[i] = arr[k];
  }

  k = first;
  int i = 0, j = 0;
  while ((i + j) < (leftArrLen + rightArrLen))
  {
    if (i == leftArrLen || j == rightArrLen)
    {
      break;
    }

    if (leftArr[i] > rightArr[j])
    {
      arr[k] = leftArr[i];
      inversions += rightArrLen - j;
      ++i;
    }
    else
    {
      arr[k] = rightArr[j];
      ++j;
    }
    ++k;
  }

  if (i == leftArrLen)
  {
    while (j < rightArrLen)
    {
      arr[k] = rightArr[j];
      ++j;
      ++k;
    }
  }

  if (j == rightArrLen)
  {
    while (i < leftArrLen)
    {
      arr[k] = leftArr[i];
      ++i;
      ++k;
    }
  }

  return inversions;
}

// Find inversions
int findInversions(int arr[], int first, int last)
{
  if (last > first)
  {
    int mid = (first + last) / 2;
    int leftPartInversions = findInversions(arr, first, mid);
    int rightPartInversions = findInversions(arr, mid + 1, last);
    int currentPartInversions = mergeAndCalculate(arr, first, mid, last);
    return leftPartInversions + rightPartInversions + currentPartInversions;
  }
  else
  {
    return 0;
  }
}

// Main function
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "error: expected one file as an argument\n");
    fprintf(stderr, "Correct usage: ./main input\n");
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

  for (int i = 0; i < numOfArrElems; ++i)
  {
    if (fscanf(inputFilePtr, "%d", &arr[i]) != 1)
    {
      fprintf(stderr, "error: data not found after %d elements\n", i);
      return 5;
    }
  }

  int inversions = findInversions(arr, 0, numOfArrElems - 1);
  printf("Number of inversion pairs = %d\n", inversions);

  fclose(inputFilePtr);
  return 0;
}
