#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct Stack{
    int data[SIZE];
    int top;
}Stack;

void initializeStack(Stack* stack){
    stack->top = -1;
}

int isEmpty(Stack* stack){
    return stack->top == -1;
}

int isFull(Stack* stack){
    return stack->top >= SIZE - 1;
}

void push(Stack* stack, int data){
    if(isFull(stack)){
        printf("Stack Overflow");
        return;
    }
    stack->data[++stack->top] = data;
}

int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack Underflow");
        return -1;
    }
    return stack->data[stack->top--];
}

int main(int argc, char const *argv[])
{
    Stack stack;
    initializeStack(&stack);
    push(&stack, 10);
    printf("%d \n", pop(&stack));
    return 0;
}

