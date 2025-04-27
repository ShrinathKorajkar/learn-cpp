#include <stdio.h>
#include <string.h>

/*
    Q: Sort the string in alphabetical order
    Input : bbccdefbbaa
    Output : aabbbbccdef
*/

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char *str, int low, int high)
{
    char pivot = str[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (str[j] <= pivot)
        {
            i++;
            swap(&str[i], &str[j]);
        }
    }
    swap(&str[i + 1], &str[high]);
    return i + 1;
}

void quickSort(char *str, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(str, low, high);
        quickSort(str, low, pivotIndex - 1);
        quickSort(str, pivotIndex + 1, high);
    }
}

int main()
{
    char str[] = "bbccdefbbaa";
    int n = strlen(str);
    quickSort(str, 0, n - 1);
    printf("Sorted string: %s\n", str);
    return 0;
}