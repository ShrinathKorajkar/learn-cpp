/*
    Non Stable and In Place Algo
    avg - O(N log N)        worst - O(N ^ 2)
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high){
    int pivot = arr[high];
    int i = (low - 1);
    for(int j = low; j < high; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quickSort(int *arr, int low, int high){
    if(low < high){
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort(arr, pivot + 1, high);
    }
}

void printArray(int *arr, int len){
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int arr[] = {1,3,4,5,1,5,8,9,1,3,4,0,9,0,1};
    int len = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, len);
    quickSort(arr, 0, len-1);
    printArray(arr, len);
    return 0;
}
