#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int capacity;
    int size;
} MaxHeap;

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->arr = (int*)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bottomToTopHeapify(MaxHeap* heap, int i) {
    int parent = (i - 1) / 2;

    if (parent >= 0 && heap->arr[parent] < heap->arr[i]) {
        swap(&(heap->arr[parent]), &(heap->arr[i]));
        bottomToTopHeapify(heap, parent);
    }
}

void insert(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        // Reallocate memory with 1.5 times the current capacity
        int newCapacity = heap->capacity * 1.5;
        int* newArr = (int*)realloc(heap->arr, sizeof(int) * newCapacity);
        if (newArr == NULL) {
            printf("Memory reallocation failed. Cannot insert.\n");
            return;
        }
        heap->arr = newArr;
        heap->capacity = newCapacity;
    }

    heap->size++;
    heap->arr[heap->size - 1] = value;
    bottomToTopHeapify(heap, heap->size - 1);
}

void printHeap(MaxHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

void destroyHeap(MaxHeap* heap) {
    free(heap->arr);
    free(heap);
}



void topToBottomHeapify(MaxHeap* heap, int i, int size) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap->arr[left] > heap->arr[largest])
        largest = left;

    if (right < size && heap->arr[right] > heap->arr[largest])
        largest = right;

    if (largest != i) {
        swap(&(heap->arr[i]), &(heap->arr[largest]));
        topToBottomHeapify(heap, largest, size);
    }
}

void extractMax(MaxHeap* heap, int size) {
    swap(&heap->arr[0], &(heap->arr[size]));
    topToBottomHeapify(heap, 0, size);
}

void heapSort(MaxHeap* heap) {
    int size = heap->size;
    while(size-- > 0){
        extractMax(heap, size);
    }
}

int main() {
    MaxHeap* heap = createHeap(10);

    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 30);
    insert(heap, 40);
    insert(heap, 10);
    insert(heap, 5);

    printHeap(heap);
    heapSort(heap);
    printHeap(heap);

    destroyHeap(heap);
    return 0;
}
