#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Q: The count-and-say sequence is a sequence of strings generated based on the previous string.
    The sequence starts with "1". Each subsequent string describes the previous string in terms of counting the
    occurrences of each digit. For example, the sequence starts as "1", "11", "21", "1211", "111221", and so on.
    Given length of sequence, print the sequence.
    input: 4
    output: "1", "11", "21", "1211"
*/

#define Qsize 100
typedef struct Queue
{
    int queue[Qsize];
    int front, rear;
} Queue;

Queue *mainQ, *helperQ;

bool isEmpty(Queue *Q)
{
    return Q->front == -1;
}

bool isFull(Queue *Q)
{
    return Q->rear == Q->front;
}

Queue *insert(Queue *Q, int elem)
{
    if (isEmpty(Q))
    {
        Q->front = Q->rear = 0;
        Q->queue[Q->rear++] = elem;
        return Q;
    }

    if (isFull(Q))
    {
        printf("Overflow");
        return Q;
    }
    Q->queue[Q->rear++] = elem;
    Q->rear = Q->rear % Qsize;
    return Q;
}

int delete(Queue *Q)
{
    int element = Q->queue[Q->front++];
    Q->front = Q->front % Qsize;

    if (Q->front == Q->rear)
    {
        Q->front = Q->rear = -1;
    }
    return element;
}

Queue *init(Queue *Q)
{
    Q = malloc(sizeof(Queue));
    Q->front = Q->rear = -1;
    return Q;
}

void printSequence(int length)
{
    mainQ = init(mainQ);
    helperQ = init(helperQ);
    insert(mainQ, 1);

    while (length-- > 0)
    {
        int count = 1;
        int prevElem = delete (mainQ);
        printf("%d", prevElem);

        while (!isEmpty(mainQ))
        {
            int elem = delete (mainQ);
            printf("%d", elem);
            if (prevElem == elem)
            {
                count++;
            }
            else
            {
                insert(helperQ, count);
                insert(helperQ, prevElem);
                prevElem = elem;
                count = 1;
            }
        }

        insert(helperQ, count);
        insert(helperQ, prevElem);

        while (!isEmpty(helperQ))
        {
            insert(mainQ, delete (helperQ));
        }

        printf(", ");
    }
    free(mainQ);
    free(helperQ);
}

int main()
{
    int sequenceLength = 4;
    printSequence(sequenceLength);
    return 0;
}