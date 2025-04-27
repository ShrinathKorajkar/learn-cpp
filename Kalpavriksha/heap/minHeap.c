#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeap{
    int *arr;
    int capacity;
    int size;
}MinHeap;

MinHeap *createMinHeap(){
    int capacity = 5;
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->arr = malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bottomUpHeapify(MinHeap *heap, int i){
    int parent = (i - 1) / 2;
    if(parent >= 0 && heap->arr[parent] > heap->arr[i]){
        swap(&heap->arr[parent], &heap->arr[i]);
        bottomUpHeapify(heap, parent);
    }
}

void insert(MinHeap *heap, int data){
    if(heap->size == heap->capacity - 1){
        heap->capacity *= 1.5;
        heap->arr = realloc(heap->arr, heap->capacity * sizeof(MinHeap));
    }
    heap->size++;
    heap->arr[heap->size - 1] = data;
    bottomUpHeapify(heap, heap->size - 1);
}

void topDownHeapify(MinHeap *heap, int i){
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int smallest = i;
    
    if(leftChild < heap->size && heap->arr[leftChild] < heap->arr[smallest]){
        smallest = leftChild;
    }
    if(rightChild < heap->size && heap->arr[rightChild] < heap->arr[smallest]){
        smallest = rightChild;
    }

    if(smallest != i){
        swap(&heap->arr[smallest], &heap->arr[i]);
        topDownHeapify(heap, smallest);
    }
}

int extractMin(MinHeap *heap){
    if(heap->size == -1){
        return -1;
    }
    int temp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size];
    heap->arr[heap->size] = temp;
    heap->size--;
    topDownHeapify(heap, 0);
    return temp;
}

void printHeap(MinHeap *heap){
    int *arr = heap->arr;
    for(int i = 0; i < heap->size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void destroyHeap(MinHeap *heap){
    free(heap->arr);
    free(heap);
}

int main(){
    MinHeap *heap = createMinHeap();
    insert(heap, 40);
    insert(heap, 20);
    insert(heap, 10);
    insert(heap, 30);

    printHeap(heap);
    printf("%d\n", extractMin(heap));
    printHeap(heap);

    destroyHeap(heap);
    return 0;
}