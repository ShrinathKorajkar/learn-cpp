/*
    Q: Remove duplicates from sorted array
    input  :-  arr[] = {1, 1, 2, 3, 4, 5, 5, 6, 7, 7, 7}
    output :-  arr[] = {1, 2, 3, 4, 5, 6, 7}
*/

#include <stdio.h>
int removeDuplicates(int *arr, int len){
    int firstPointer = 1, secondPointer = 1;
    int previousElem = arr[0];
    for(int i = 1; i < len; i++){
        if(arr[i] == previousElem){
            secondPointer++;
        }else{
            arr[firstPointer++] = arr[secondPointer];
            previousElem = arr[secondPointer++];
        }
    }
    return firstPointer;
}

void printWithoutDuplicates(int *arr, int len){
    int newLen = removeDuplicates(arr, len);
    printf("Array without duplicates : ");
    for(int i = 0; i < newLen; i++){
        printf("%d  ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int arr[] = {1, 1, 2, 2, 3, 4, 5, 6, 6, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
    printWithoutDuplicates(arr, len);
    return 0;
}