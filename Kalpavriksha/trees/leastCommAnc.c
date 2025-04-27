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

void destroyTree(Node *root){
    if(root == NULL){
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

Node *findLCA(Node *root, int num1, int num2){
    if(root == NULL){
        return NULL;
    }
    if(root->data == num1 || root->data == num2){
        return root;
    }
    Node *leftLca = findLCA(root->left, num1, num2);
    Node *rightLca = findLCA(root->right, num1, num2);
    if(leftLca != NULL && rightLca != NULL){
        return root;
    }
    return leftLca == NULL ? rightLca : leftLca;
}

void printLeastCommonAncestor(Node *root, int num1, int num2){
    Node *lca = findLCA(root, num1, num2);
    if(lca){
        printf("Least Common ancestor : %d\n", lca->data);
    }
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

    printLeastCommonAncestor(root, 30, 10);

    destroyTree(root);
    return 0;
}

/*
                  50
        20                  70
    10     30           60       80
                40
*/
