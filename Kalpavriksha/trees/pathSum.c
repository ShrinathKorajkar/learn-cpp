#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node* createNode(int data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node *root, int data){
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

void destroyTree(Node *root){
    if(root == NULL){
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

bool rootToLeaf(Node *root, int sum, int currentSum){
    if(root == NULL){
        return false;
    }
    currentSum += root->data;
    if(currentSum == sum && root->left == NULL && root->right == NULL){
        return true;
    }
    return rootToLeaf(root->left, sum, currentSum) || rootToLeaf(root->right, sum, currentSum);
}

int main()
{
    Node *root = NULL;
    root = insertNode(root, 5);
    insertNode(root, 4);
    insertNode(root, 8);
    insertNode(root, 11);
    insertNode(root, 13);
    insertNode(root, 4);
    insertNode(root, 7);
    insertNode(root, 2);
    insertNode(root, 1);

    bool found = rootToLeaf(root, 12, 0);
    if(found){
        printf("True");
    }else{
        printf("False");
    }

    destroyTree(root);
    return 0;
}
