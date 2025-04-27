/*
    Q: Given array of N integers. for 1 < k < n. choose element from arr, remove it from arr
       for each i from k to n. you have to maximize the score.
    input: arr[] = {5 8 3 2}
    output: 18 16 13 8
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue *createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->arr = (int *)malloc(capacity * sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->arr[index] < pq->arr[parent]) {
        swap(&pq->arr[index], &pq->arr[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapifyDown(PriorityQueue *pq, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < pq->size && pq->arr[left] < pq->arr[smallest]) {
        smallest = left;
    }

    if (right < pq->size && pq->arr[right] < pq->arr[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pq->arr[index], &pq->arr[smallest]);
        heapifyDown(pq, smallest);
    }
}

void insert(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        return; // Priority queue is full
    }

    pq->arr[pq->size] = value;
    pq->size++;

    heapifyUp(pq, pq->size - 1);
}

int removeMin(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1; // Priority queue is empty
    }

    int min = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;

    heapifyDown(pq, 0);

    return min;
}

void destroyPriorityQueue(PriorityQueue *pq) {
    free(pq->arr);
    free(pq);
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases-- > 0) {
        int n;
        scanf("%d", &n);

        int *arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        PriorityQueue *pq = createPriorityQueue(n);

        long sum = 0;
        for (int i = 0; i < n; i++) {
            insert(pq, arr[i]);
            sum += arr[i];
        }

        for (int i = 0; i < n; i++) {
            printf("%ld ", sum);
            sum -= removeMin(pq);
        }

        printf("\n");

        destroyPriorityQueue(pq);
        free(arr);
    }

    return 0;
}
