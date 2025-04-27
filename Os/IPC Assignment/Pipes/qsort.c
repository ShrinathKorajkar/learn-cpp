#include "qsort.h"

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int left, int right)
{
    int pivot = arr[right];
    int first = left;

    for (int second = left; second < right; second++)
    {
        if (arr[second] < pivot)
        {
            swap(&arr[first], &arr[second]);
            first++;
        }
    }

    swap(&arr[first], &arr[right]);
    return first;
}

void quickSort(int *array, int left, int right)
{
    if (left < right)
    {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot - 1);
        quickSort(array, pivot + 1, right);
    }
}