#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

bool isQEmpty(Queue *queue)
{
    return queue->front == NULL;
}

void insertItem(Queue *queue, int data)
{
    Node *temp = malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;

    if (isQEmpty(queue))
    {
        queue->front = queue->rear = temp;
        return;
    }

    queue->rear->next = temp;
    queue->rear = temp;
}

int removeItem(Queue *queue)
{
    if (isQEmpty(queue))
    {
        return -1;
    }
    Node *curr = queue->front;
    queue->front = curr->next;
    if (isQEmpty(queue))
    {
        queue->rear = NULL;
    }
    return curr->data;
}

Queue *initQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

Queue *takeInput()
{
    Queue *queue = initQueue();
    int size = 0;
    printf("\nEnter size of List: ");
    scanf("%d", &size);
    int data = 0;
    printf("Enter List Items : \n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &data);
        insertItem(queue, data);
    }
    return queue;
}

int findSecondLeastPositive(Queue *queue)
{
    int leastPositive = INT_MAX, secondLeastPositive = INT_MAX;
    while (!isQEmpty(queue))
    {
        int data = removeItem(queue);
        if (data > 0)
        {
            if (data < leastPositive)
            {
                secondLeastPositive = leastPositive;
                leastPositive = data;
            }
            else if (data < secondLeastPositive)
            {
                secondLeastPositive = data;
            }
        }
    }
    return secondLeastPositive;
}

int main()
{
    Queue *queue = takeInput();
    int secondLeastPositive = findSecondLeastPositive(queue);
    printf("Second Least Positive : %d\n", secondLeastPositive);
    return 0;
}