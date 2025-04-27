#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

Node *createNode(char *timestamp, char *deviceState)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->timestamp, timestamp);
    strcpy(newNode->deviceState, deviceState);
    newNode->next = NULL;
    return newNode;
}

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue)
{
    return (queue->front == NULL);
}

void enqueue(Queue *queue, char *timestamp, char *deviceState)
{
    Node *newNode = createNode(timestamp, deviceState);
    if (isEmpty(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Node *dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        exit(1);
    }

    Node *temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    return temp;
}

void displayQueue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }
    Node *current = queue->front;
    printf("\nElements in the queue are:\n");
    while (current != NULL)
    {
        printf("Timestamp: %s, Device State: %s\n", current->timestamp, current->deviceState);
        current = current->next;
    }
}

void destroyQueue(Queue *queue)
{
    Node *current = queue->front;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(queue);
}
