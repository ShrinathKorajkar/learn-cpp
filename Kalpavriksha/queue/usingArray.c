/*
    QUEUE:
    1. linear Ds, FIFO
    2. enqueue, dequeue, front, rear, isEmpty, size
    3. array, linkedList
    4. job scheduling, task management, BFS, mesg Queues, Cpu scheduling    
    5. Circulat Q, Priority Q
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 10

typedef struct{
    int data[SIZE];
    int front, rear;
}Queue;

void initialize(Queue* queue){
    queue->front = queue->rear = -1;
}

bool isEmpty(Queue* queue){
    return queue->front == -1;
}

bool isFull(Queue* queue){
    return queue->rear == SIZE - 1;
}

void enqueue(Queue* queue, int value){
    if(isFull(queue)){
        printf("Queue is full\n");
        return;
    }
    if(isEmpty(queue)){
        queue->front++;
    }
    queue->data[++queue->rear] = value;
}

int dequeue(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return -1;
    }
    int val = queue->data[queue->front++];
    if(queue->front > queue->rear){
        queue->front = queue->rear = -1;
    }
    return val;
}

int front(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return -1; 
    }
    return queue->data[queue->front];
}

int main(int argc, char const *argv[])
{
    Queue *queue = malloc(sizeof(Queue));
    initialize(queue);
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    free(queue);
    return 0;
}
