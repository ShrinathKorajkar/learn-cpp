/*
    Q: Find the next greater element (greater element in right) in the given array.
    input  :-  arr[] = {1, 3, 4, 2}
    output :-  {3, 4, -1, -1}
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 10

typedef struct {
    int data[SIZE];
    int top;
}Stack;

void initialize(Stack *stack){
    stack->top = -1;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

bool isFull(Stack *stack) {
    return stack->top >= SIZE - 1;
}

void push(Stack *stack, int data){
    if(isFull(stack)){
        printf("Overflow");
        return;
    }
    stack->data[++stack->top] = data;
}

int pop(Stack *stack){
    if(isEmpty(stack)){
        printf("Underflow");
        return -1;
    }
    return stack->data[stack->top--];
}

int peek(Stack *stack){
    return stack->data[stack->top];
}

void nextGreaterElement(int *arr, int len, Stack *stack, int *result){
    push(stack, -1);
    for(int i = len - 1; i >= 0; i--){
        
        while(peek(stack) < arr[i] && peek(stack) != -1){
            pop(stack);
        }
        result[i] = peek(stack);
        push(stack, arr[i]);
        
    }
}

void printNextGreaterElement(int *arr, int len, Stack *stack){
    int *newArr = malloc(len * sizeof(int));
    nextGreaterElement(arr, len, stack, newArr);
    for(int i = 0; i < len; i++){
        printf("%d ", newArr[i]);
    }
    printf("\n");
    free(newArr);
}

int main(int argc, char const *argv[])
{
    Stack *stack = malloc(sizeof(Stack));
    initialize(stack);
    int arr[] = {1, 3, 4, 2};
    int len = sizeof(arr) / sizeof(arr[0]);
    printNextGreaterElement(arr, len, stack);
    free(stack);
    return 0;
}
