#include <stdio.h>   // For printf, NULL
#include <time.h>    // For time
#include <stdlib.h>  // For rand, srand
#include <stdbool.h> // For true, false

// The intervals user gonna input
struct interval
{
    int start;
    int end;
};

// The parts datastructure to partition our array into three areas
// Suppose array is indexed as (0....len - 1)
// First area = [0,i) are values less than the pivot
// Second area = [i, k) are values that overlap
// Third area = [k, len-1] are values greater than pivot
struct partsData
{
    int i;
    int k;
};

// Swap intervals
void swapIntervals(struct interval *a, struct interval *b)
{
    struct interval temp = *b;
    *b = *a;
    *a = temp;
}

// Check if the intervals overlap
// Return true if overlapping else false
bool areIntervalsOverlapping(struct interval a, struct interval b)
{
    if (b.start >= a.start && b.start <= a.end)
    {
        return true;
    }
    else if (b.end >= a.start && b.end <= a.end)
    {
        return true;
    }
    else if (b.start <= a.start && b.end >= a.end)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Partition the intervals array into three zones
struct partsData partition(struct interval *intervals, int startIndex, int endIndex)
{
    struct partsData parts = {0, 0};
    int pivot = rand() % (endIndex - startIndex + 1);

    for (int j = 0; j <= endIndex; ++j)
    {
        if (areIntervalsOverlapping(intervals[j], intervals[pivot]) == true)
        {
            swapIntervals(&intervals[parts.k], &intervals[j]);
            ++parts.k;
        }
        else if (intervals[j].end < intervals[pivot].start)
        {
            swapIntervals(&intervals[parts.k], &intervals[j]);
            swapIntervals(&intervals[parts.k], &intervals[parts.i]);
            ++parts.i;
            ++parts.k;
        }
    }

    return parts;
}

// Fuzzy sort the intervals
void fuzzySort(struct interval *intervals, int startIndex, int endIndex)
{
    if (endIndex > startIndex)
    {
        struct partsData parts = partition(intervals, startIndex, endIndex);
        fuzzySort(intervals, startIndex, parts.i - 1);
        fuzzySort(intervals, parts.k, endIndex);
    }
}

// Main function
int main(void)
{
    struct interval intervals[] = {{2, 3}, {0, 1}, {4, 8}, {10, 10}};
    int len = sizeof intervals / sizeof intervals[0];

    printf("BEFORE FUZZY SORTING:\n");
    for (int i = 0; i < len; ++i)
    {
        printf("%d to %d  ", intervals[i].start, intervals[i].end);
    }
    printf("\n\n");

    srand(time(NULL));
    fuzzySort(intervals, 0, len - 1);

    printf("AFTER FUZZY SORTING:\n");
    for (int i = 0; i < len; ++i)
    {
        printf("%d to %d  ", intervals[i].start, intervals[i].end);
    }
    printf("\n");

    return 0;
}
