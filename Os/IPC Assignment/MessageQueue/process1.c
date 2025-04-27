/*
    This process receives data from process 2 -> sort the data -> send the data back
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include "qsort.h"
#define MAXSIZE 100

typedef struct
{
    long type;
    int data[MAXSIZE];
    int len;
} Message;

int createMessageQueue(char id)
{
    key_t key = ftok(".", id);
    return msgget(key, IPC_CREAT | 0666);
}

void prepareDataToSend(Message *dest, Message *source)
{
    source->len = dest->len;
    for (int i = 0; i < dest->len; i++)
    {
        source->data[i] = dest->data[i];
    }
}

int main()
{
    printf("Process 1 Started...\n");

    int sendMessageId = createMessageQueue('R');
    int receiveMessageId = createMessageQueue('S');

    Message sendMessage, receiveMessage;
    sendMessage.type = 1;
    receiveMessage.type = 1;

    msgrcv(receiveMessageId, &receiveMessage, sizeof(receiveMessage), 1, 0);
    msgctl(receiveMessageId, IPC_RMID, NULL);

    printf("Data read, Sorting...\n");
    quickSort(receiveMessage.data, 0, receiveMessage.len - 1);

    prepareDataToSend(&receiveMessage, &sendMessage);

    printf("Data sorted and sending...\n");
    msgsnd(sendMessageId, &sendMessage, sizeof(sendMessage), 0);

    return 0;
}
