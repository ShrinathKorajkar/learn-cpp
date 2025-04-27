#include <stdio.h>
#include <stdlib.h>

// Comparison function for sorting integers in ascending order
int compareIntegers(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), compareIntegers);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
