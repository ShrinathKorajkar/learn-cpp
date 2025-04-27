#ifndef QUEUE_H
#define QUEUE_H

#define timestampLength 25
#define deviceStateLength 5

typedef struct Node
{
    char timestamp[timestampLength];
    char deviceState[deviceStateLength];
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

Node *createNode(char *timestamp, char *deviceState);
Queue *createQueue();
int isEmpty(Queue *queue);
void enqueue(Queue *queue, char *timestamp, char *deviceState);
Node *dequeue(Queue *queue);
void displayQueue(Queue *queue);
void destroyQueue(Queue *queue);

#endif // QUEUE_H
