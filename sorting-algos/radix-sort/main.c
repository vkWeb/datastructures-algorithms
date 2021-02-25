#include <stdio.h> // For printf

// Returns the digit of the input `place`
// E.g. if n = 522 and place = 3, then 5 will be returned
// because 5 is in third place
int getDigitOfNumByPlace(int n, const int place)
{
#include <math.h>
    n = n / ((int)pow(10, place - 1));
    return n % 10;
}

// Do radix sort using counting sort as an intermediate sorter
// Sorts `arr`
void radixSort(int *arr, const int n, const int d)
{
    int tempArr[n];

    for (int i = 1; i <= d; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tempArr[j] = arr[j];
        }

        int countArr[10] = {0};
        for (int j = 0; j < n; ++j)
        {
            int digit = getDigitOfNumByPlace(tempArr[j], i);
            ++countArr[digit];
        }

        for (int j = 1; j < 10; ++j)
        {
            countArr[j] += countArr[j - 1];
        }

        for (int j = n - 1; j >= 0; --j)
        {
            int digit = getDigitOfNumByPlace(tempArr[j], i);
            int positionOfJthElem = countArr[digit] - 1;
            arr[positionOfJthElem] = tempArr[j];
            --countArr[digit];
        }
    }
}

int main(void)
{
    int arr[] = {3240, 1526, 3122, 9421, 1048, 7604};
    int n = sizeof(arr) / sizeof(arr[0]);
    radixSort(arr, n, 4);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
