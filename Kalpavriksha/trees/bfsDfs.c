#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node *createNode(int data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *root, int data){
    if(root == NULL){
        return createNode(data);
    }
    if(data < root->data){
        root->left = insertNode(root->left, data);
    }else{
        root->right = insertNode(root->right, data);
    }
    return root;
}

Node *findMin(Node *root){
    Node *current = root;
    while(current && current->left != NULL){
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int value){
    if(root == NULL){
        return root;
    }
    if(value < root->data){
        root->left = deleteNode(root->left, value);
    }else if(value > root->data){
        root->right = deleteNode(root->right, value);
    }else{
        if(root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }else if(root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        }
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

typedef struct QueueNode {
    Node* data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, Node* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
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

Node* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }

    QueueNode* frontNode = queue->front;
    Node* data = frontNode->data;

    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }

    free(frontNode);
    return data;
}

void destroyQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

void bfs(Node *root){
    if(root == NULL){
        return;
    }
    Queue *queue = createQueue();
    enqueue(queue, root);
    while(!isEmpty(queue)){
        Node *current = dequeue(queue);
        printf("%d ", current->data);
        if(current->left != NULL){
            enqueue(queue, current->left);
        }
        if(current->right != NULL){
            enqueue(queue, current->right);
        }
    }
    destroyQueue(queue);
}

void dfs(Node *root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->data);
    dfs(root->left);
    dfs(root->right);
}

int main()
{
    Node *root = NULL;
    root = insertNode(root, 10);
    insertNode(root, 3);
    insertNode(root, 15);
    insertNode(root, 9);
    insertNode(root, 20);
    insertNode(root, 18);
    insertNode(root, 12);
    insertNode(root, 7);
    insertNode(root, 14);
    insertNode(root, 1);

    printf("BFS :-");
    bfs(root);
    printf("\nDfS :-");
    dfs(root);

    return 0;
}
