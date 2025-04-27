#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
    This process reads the input -> send data to process 1 -> receive data from process 1 -> display the data
*/
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

    free(array);
}

void init(int *clientSocket, struct sockaddr_in *serverAddress)
{
    *clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress->sin_family = AF_INET;
    serverAddress->sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress->sin_port = htons(5000);
}

int main()
{
    printf("Process 2 Started...\n");
    int len = 0;
    int *array = takeInput(&len);

    int clientSocket;
    struct sockaddr_in serverAddress;

    init(&clientSocket, &serverAddress);

    printf("Connecting to Server\n");
    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    printf("Connected to Server. Sending Data...\n");
    send(clientSocket, &len, sizeof(len), 0);
    send(clientSocket, array, sizeof(int) * len, 0);

    printf("Data sent. Waiting for Sorted Data...\n");
    recv(clientSocket, array, sizeof(int) * len, 0);

    printf("Data Received.\n");
    printSortedResult(array, len);

    close(clientSocket);
    return 0;
}
