#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void init(Stack* stack) {
    stack->top = NULL;
}

bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow.\n");
        return -1;
    }
    Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->top->data;
}

void destroyStack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Stack stack;
    init(&stack);
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    printf("Peek: %d\n", peek(&stack));

    int data = pop(&stack);
    printf("Popped: %d\n", data);

    destroyStack(&stack);

    return 0;
}
