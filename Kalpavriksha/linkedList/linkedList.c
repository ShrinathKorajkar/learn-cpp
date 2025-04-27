/*
    Dynamic memory allocation. Node - data, pointer to next
    a. head node, tail node
    b. singly LL, Doubly LL, Circular LL
    c. insertion, deletion, traversing, searching
    d. Adv- dynamic size, efficient insertion and deletion, memory efficient, versatile - used to implement other ds
    e. disadv - random access ineff, additonal mem, sequential access.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct {
    Node *head;
    Node *tail;
}list;

void init(list *linkedList){
    linkedList->head = NULL;
    linkedList->tail = NULL;
}

bool isEmpty(list *linkedList){
    return linkedList->head == NULL;
}

void printList(list *linkedList){
    Node *current = linkedList->head;
    while(current!= NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void insertAtBeginning(list *linkedList, int data){
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if(isEmpty(linkedList)){
        linkedList->head = node;
        linkedList->tail = node;
        return;
    }
    node->next = linkedList->head;
    linkedList->head = node;
}

int removeAtBeginning(list *linkedList){
    if(isEmpty(linkedList)){
        return -1;
    }
    Node *temp = linkedList->head;
    if(linkedList->head == linkedList->tail){
        linkedList->head = NULL;
        linkedList->tail = NULL;
    }else{
        linkedList->head = linkedList->head->next;
    }
    int data = temp->data;
    free(temp);
    return data;
}

void insertAtEnd(list *linkedList, int data){
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if(isEmpty(linkedList)){
        linkedList->head = node;
        linkedList->tail = node;
        return;
    }
    linkedList->tail->next = node;
    linkedList->tail = node;
}

int removeAtEnd(list *linkedList){
    if(isEmpty(linkedList)){
        return -1;
    }
    Node *temp = linkedList->tail;
    Node *current = linkedList->head;
    if(linkedList->head == linkedList->tail){
        linkedList->head = NULL;
        linkedList->tail = NULL;
    }else{
        while(current->next != linkedList->tail){
            current = current->next;
        }
        linkedList->tail = current;
        current->next = NULL;
    }
    int data = temp->data;
    free(temp);
    return data;
}

int search(list *linkedList, int value){
    Node *current = linkedList->head;
    while(current!= NULL){
        if(current->data == value){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void destroyList(list *linkedList){
    Node *current = linkedList->head;
    while(current!= NULL){
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(linkedList);
}

int main(int argc, char const *argv[])
{
    list *linkedList = malloc(sizeof(list));
    init(linkedList);
    insertAtBeginning(linkedList, 1);
    insertAtBeginning(linkedList, 2);
    insertAtBeginning(linkedList, 3);
    insertAtEnd(linkedList, 4);
    insertAtEnd(linkedList, 5);
    insertAtEnd(linkedList, 6);
    insertAtEnd(linkedList, 7);
    insertAtEnd(linkedList, 8);
    insertAtEnd(linkedList, 9);
    insertAtEnd(linkedList, 10);
    printList(linkedList);
    removeAtBeginning(linkedList);
    removeAtEnd(linkedList);
    printList(linkedList);
    destroyList(linkedList);
    return 0;
}
