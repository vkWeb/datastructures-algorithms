#include <stdio.h>  // For printf, NULL
#include <time.h>   // For time
#include <stdlib.h> // For rand, srand

// Exchange elements at index `i` and `j` of array `arr`
void swap(int *arr, int i, int j)
{
    int temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}

// Partition array for quicksort into two parts around pivot
// On the left of pivot, we'll have values less than or equal to pivot
// On the right, we'll have values greater than pivot
// Returns the index of pivot
int partitionArr(int *arr, int start, int end)
{
    int pivotIndex, i, j;
    pivotIndex = rand() % (end - start + 1);

    for (i = j = 0; j <= end; ++j)
    {
        if (arr[j] <= arr[pivotIndex])
        {
            if (j == pivotIndex)
            {
                pivotIndex = i;
            }
            swap(arr, i, j);
            ++i;
        }
    }

    swap(arr, i - 1, pivotIndex);
    return i - 1;
}

// The classical quicksort algorithm
void quicksort(int *arr, int start, int end)
{
    if (end > start)
    {
        int pivotIndex = partitionArr(arr, start, end);
        quicksort(arr, start, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, end);
    }
}

// Main function
int main(void)
{
    int arr[] = {1, -2, 31, 42, 5, 6, 37, -8, 19, 100, 11, 102, -13};
    int arrLen = sizeof arr / sizeof arr[0];

    srand(time(NULL));
    quicksort(arr, 0, arrLen - 1);

    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}
