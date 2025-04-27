#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 3

typedef struct{
    int data[SIZE];
    int front;
    int rear;
}Queue;

void init(Queue* cqueue){
    cqueue->front = -1;
    cqueue->rear = -1;
}

bool isEmpty(Queue* cqueue){
    return cqueue->front == -1;
}

bool isFull(Queue* cqueue){
    return (cqueue->rear + 1) % SIZE == (cqueue->front);
}

void enqueue(Queue* cqueue, int data){
    if(isFull(cqueue)){
        printf("Queue Full\n");
        return;
    }
    if(cqueue->front == -1){
        cqueue->front++;
    }
    cqueue->rear = (cqueue->rear + 1) % SIZE;
    cqueue->data[cqueue->rear] = data;
}

int dequeue(Queue* cqueue){
    if(isEmpty(cqueue)){
        printf("Queue Empty\n");
        return -1;
    }
    int value = cqueue->data[cqueue->front];
    if(cqueue-> front == cqueue->rear){
        cqueue->front = -1;
        cqueue->rear = -1;
    }else{
        cqueue->front = (cqueue->front + 1) % SIZE;
    }
    return value;
}

int main(int argc, char const *argv[])
{
    Queue *cqueue = malloc(sizeof(Queue));
    init(cqueue);
    enqueue(cqueue, 1);
    enqueue(cqueue, 2);
    enqueue(cqueue, 3);
    printf("%d\n", dequeue(cqueue));
    enqueue(cqueue, 3);
    free(cqueue);
    return 0;
}
