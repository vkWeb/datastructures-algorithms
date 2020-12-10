#include <stdio.h>

int left(int i)
{
    return ((2 * i) + 1);
}
int right(int i)
{
    return ((2 * i) + 2);
}

/* Corrects the max-heap violation at ith position */
void maxifyHeap(int arr[], int arr_size, int i)
{
    while (i < (arr_size / 2))
    {
        int largest = i;
        if (arr[left(i)] > arr[i])
        {
            largest = left(i);
        }
        if (arr[right(i)] > arr[i])
        {
            largest = right(i);
        }
        if (largest == i)
        {
            break;
        }

        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        i = largest;
    }
}

/* Builds max-heap */
void buildMaxHeap(int arr[], int arr_size)
{
    for (int i = (arr_size / 2) - 1; i >= 0; --i)
    {
        maxifyHeap(arr, arr_size, i);
    }
}

/* Sorts an array in ascending order using heapsort algorithm */
void heapSort(int arr[], int arr_size)
{
    buildMaxHeap(arr, arr_size);
    while (arr_size > 0)
    {
        int temp = arr[arr_size - 1];
        arr[arr_size - 1] = arr[0];
        arr[0] = temp;

        --arr_size;

        maxifyHeap(arr, arr_size, 0);
    }
}

/* Main function */
int main(void)
{
    int arr[] = {5, 4, 10, 23, 56, 0, -2, 5, 3, 42};
    int arr_len = sizeof arr / sizeof arr[0];

    heapSort(arr, arr_len);

    for (int i = 0; i < arr_len; ++i)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}
