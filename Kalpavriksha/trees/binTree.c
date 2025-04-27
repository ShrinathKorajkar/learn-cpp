#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node *createNode(int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node *root, int data){
    if(root == NULL){
        return createNode(data);;
    }
    if(data < root->data){
        root->left = insertNode(root->left, data);
    }else{
        root->right = insertNode(root->right, data);
    }
    return root;
}

Node *findMinNode(Node *root){
    Node *currentNode = root;
    while(currentNode && currentNode->left != NULL){
        currentNode = currentNode->left;
    }
    return  currentNode;
}

Node *deleteNode(Node *root, int data){
    if(root == NULL){
        return root;
    }
    if(data < root->data){
        root->left = deleteNode(root->left, data);
    }else if (data < root->data) {
        root->right = deleteNode(root->right, data);
    }else{
        if(root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

Node* searchNode(Node *root, int value){
    if(root == NULL || value == root->data){
        return root;
    }
    if(value < root->data){
        return searchNode(root->left, value);
    }
    return searchNode(root->right, value);
}

void preorderTraversal(Node *root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(Node *root){
    if(root == NULL){
        return;
    }
    preorderTraversal(root->left);
    printf("%d ", root->data);
    preorderTraversal(root->right);
}

void postorderTraversal(Node *root){
    if(root == NULL){
        return;
    }
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    printf("%d ", root->data);
}

void destroyTree(Node *root){
    if(root == NULL){
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int main()
{
    Node *root = NULL;
    root = insertNode(root, 50);
    insertNode(root, 20);
    insertNode(root, 10);
    insertNode(root, 30);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);

    printf("Inorder Traversal : \n");
    inorderTraversal(root);

    printf("\nPreorder Traversal : \n");
    preorderTraversal(root);

    printf("\nPostorder Traversal : \n");
    postorderTraversal(root);

    Node *search = searchNode(root, 40);
    if(search != NULL){
        printf("\nNode with value found in the tree\n");
    }else{
        printf("\nNode with value not found in the tree\n");
    }

    root = deleteNode(root, 40);
    printf("Inorder Traversal After Deletion : \n");
    inorderTraversal(root);

    destroyTree(root);
    root = NULL;

    return 0;
}
