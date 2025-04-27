#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void init(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

bool isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow.\n");
        return -1;
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

int front(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->front->data;
}

void destroyQueue(Queue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Queue queue;
    init(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    printf("Front: %d\n", front(&queue));
    int data = dequeue(&queue);
    printf("Dequeued: %d\n", data);

    destroyQueue(&queue);

    return 0;
}
