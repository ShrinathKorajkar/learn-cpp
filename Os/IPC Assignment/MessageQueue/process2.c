/*
    This process reads the input -> send data to process 1 -> receive data from process 1 -> display the data
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#define MAXSIZE 100

typedef struct
{
    long type;
    int data[MAXSIZE];
    int len;
} Message;

int *takeInput(int *len)
{
    char *str = malloc(1024 * sizeof(char));

    printf("Enter numbers you want to sort : ");

    scanf("%[^\n]", str);
    *len = strlen(str);
    str = realloc(str, *len + 1);

    int *array = malloc(*len * sizeof(int));
    char *token = strtok(str, " ");

    int index = 0;
    for (; token != NULL; index++)
    {
        array[index] = atoi(token);
        token = strtok(NULL, " ");
    }
    *len = index;
    free(str);
    return array;
}

void printSortedResult(int *array, int len)
{
    printf("\nSorted elements : ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int createMessageQueue(char id)
{
    key_t key = ftok(".", id);
    return msgget(key, IPC_CREAT | 0666);
}

void createMessage(Message *sendMessage, int *array)
{
    for (int i = 0; i < sendMessage->len; i++)
    {
        sendMessage->data[i] = array[i];
    }
}

int main()
{
    printf("Process 2 Started...\n");

    Message sendMessage, receiveMessage;
    sendMessage.len = 0;
    sendMessage.type = 1;
    receiveMessage.type = 1;

    int *array = takeInput(&sendMessage.len);

    int sendMessageId = createMessageQueue('S');
    int receiveMessageId = createMessageQueue('R');

    createMessage(&sendMessage, array);

    msgsnd(sendMessageId, &sendMessage, sizeof(sendMessage), 0);

    msgrcv(receiveMessageId, &receiveMessage, sizeof(receiveMessage), 1, 0);

    printSortedResult(receiveMessage.data, receiveMessage.len);

    msgctl(receiveMessageId, IPC_RMID, NULL);
    free(array);

    return 0;
}
