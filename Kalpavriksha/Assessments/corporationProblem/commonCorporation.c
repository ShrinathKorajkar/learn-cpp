#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LENGTH 100

typedef struct Node
{
    char data[MAX_DATA_LENGTH];
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *createNode(const char *data, Node *parent)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

void insertChildren(Node *root, const char *leftData, const char *rightData)
{
    if (root == NULL)
    {
        return;
    }

    Node *leftChild = createNode(leftData, root);
    Node *rightChild = createNode(rightData, root);

    root->left = leftChild;
    root->right = rightChild;
}

void displayTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%s ", root->data);
    displayTree(root->left);
    displayTree(root->right);
}

void destroyTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

typedef struct QueueNode
{
    Node *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

void enqueue(Queue *queue, Node *data)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL)
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
    if (queue->front == NULL)
    {
        return NULL;
    }

    QueueNode *frontNode = queue->front;
    Node *data = frontNode->data;

    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(frontNode);
    return data;
}

Node *findNodeWithValue(Node *root, const char *value)
{
    if (root == NULL)
        return NULL;

    if (strcmp(root->data, value) == 0)
        return root;

    Node *leftResult = findNodeWithValue(root->left, value);
    if (leftResult != NULL)
        return leftResult;

    Node *rightResult = findNodeWithValue(root->right, value);
    if (rightResult != NULL)
        return rightResult;

    return NULL;
}

Node *findCommonParent(Node *node1, Node *node2)
{
    if (node1 == NULL || node2 == NULL)
        return NULL;

    Node *p1 = node1;
    Node *p2 = node2;

    while (p1 != p2)
    {
        p1 = p1->parent;
        p2 = p2->parent;
    }

    return p1;
}

void printCommonTerms(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%s, ", root->data);
    printCommonTerms(root->parent);
}

Node *takeInput(FILE *ptr)
{
    Node *root = NULL;
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    char data[MAX_DATA_LENGTH];
    char leftData[MAX_DATA_LENGTH];
    char rightData[MAX_DATA_LENGTH];

    fscanf(ptr, "%s\n", data);

    root = createNode(data, NULL);
    enqueue(queue, root);

    while (fscanf(ptr, "%[^,], %s\n", leftData, rightData) == 2)
    {
        Node *parentNode = dequeue(queue);
        Node *leftChild = createNode(leftData, parentNode);
        parentNode->left = leftChild;
        enqueue(queue, leftChild);

        Node *rightChild = createNode(rightData, parentNode);
        parentNode->right = rightChild;
        enqueue(queue, rightChild);
    }

    free(queue);

    return root;
}

int main()
{
    FILE *ptr = fopen("../inputFile.txt", "r");
    if (ptr == NULL)
    {
        printf("No such file.\n");
        return 0;
    }

    Node *root = takeInput(ptr);

    // displayTree(root);

    char corporation1[10];
    char corporation2[10];
    scanf("%[^,], %s", corporation1, corporation2);

    Node *corpNode1 = findNodeWithValue(root, corporation1);
    Node *corpNode2 = findNodeWithValue(root, corporation2);

    if (corpNode1 == NULL || corpNode2 == NULL)
    {
        printf("\nError: Invalid Corporation value");
    }
    else
    {
        printf("Common Terms Are :\n");
        Node *commonParent = findCommonParent(corpNode1, corpNode2);
        printCommonTerms(commonParent);
    }

    destroyTree(root);

    return 0;
}
