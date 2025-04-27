/*
    STACK  =>  linear DS, LIFO
    a. hardware     :-  region of contigous blocks, stackPointer(SP), basePointer(BP)
    b. application  :-  os, compilers, recursion, expression evaluation, function calls, DFS, backtracking
    c. call stack | execution stack
    d. operations   :-  push, pop, peek, isEmpty, isFull
    e. advantages   :-  push, pop, peek => O(1)
    f. disadvantages:-  limited capacity (~8Mb), random access
    g. stack overflow, underflow
*/

#include <stdio.h>
#include <stdbool.h>
#define stackSize 10
int stack[stackSize];
int top = -1;

bool stackIsFull(){
    return top >= stackSize - 1;
}

bool stackIsEmpty(){
    return top == -1;
}

void push(int data){
    if(stackIsFull()){
        printf("Stack overflow");
        return;
    }
    stack[++top] = data;
}

int pop(){
    if(stackIsEmpty()){
        printf("Stack Underflow");
        return -1;
    }
    return stack[top--];
}

int main(int argc, char const *argv[])
{
    push(10);
    push(20);
    push(30);
    printf("%d \n", pop());
    printf("%d \n", pop());
    printf("%d \n", pop());
    return 0;
}
