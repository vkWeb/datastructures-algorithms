#include <stdio.h>

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
    pivotIndex = start;
    i = j = start + 1;

    while (j <= end)
    {
        if (arr[j] <= arr[pivotIndex])
        {
            swap(arr, i, j);
            ++i;
        }
        ++j;
    }

    swap(arr, i - 1, pivotIndex);
    return i - 1;
}

// The classical quicksort algorithm
void quicksort(int *arr, int start, int end)
{
    if (start > end)
    {
        int pivotIndex = partitionArr(arr, start, end);
        quicksort(arr, start, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, end);
    }
}

// Main function
int main(void)
{
    int arr[] = {13, 19, 9, 5, 12, 87, 4, 26};
    int arrLen = sizeof arr / sizeof arr[0];

    quicksort(arr, 0, arrLen - 1);

    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}
