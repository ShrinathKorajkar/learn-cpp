#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "qsort.h"

/*
    This process receives data from process 2 -> sort the data -> send the data back
*/

void init(int *serverSocket, struct sockaddr_in *serverAddress)
{
    *serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress->sin_family = AF_INET;
    serverAddress->sin_addr.s_addr = INADDR_ANY;
    serverAddress->sin_port = htons(5000);
}

void startServer(int serverSocket, struct sockaddr_in *serverAddress)
{
    int reuse = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    bind(serverSocket, (struct sockaddr *)serverAddress, sizeof(*serverAddress));

    listen(serverSocket, 2);
    printf("Server listening on port 5000...\n");
}

int receiveData(int *clientSocket, int serverSocket, int **array)
{
    *clientSocket = accept(serverSocket, NULL, NULL);
    printf("Connected to Client\n");

    int len = 0;

    recv(*clientSocket, &len, sizeof(len), 0);
    *array = malloc(len * sizeof(int));
    recv(*clientSocket, *array, sizeof(int) * len, 0);

    return len;
}

int main()
{
    printf("Process 1 Started...\n");

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;

    init(&serverSocket, &serverAddress);

    startServer(serverSocket, &serverAddress);

    int *array = NULL;
    int len = receiveData(&clientSocket, serverSocket, &array);

    printf("Data Received. Sorting...\n");
    quickSort(array, 0, len - 1);

    printf("Data sorted. Sending Data...\n");
    send(clientSocket, array, sizeof(int) * len, 0);
    printf("Data sent.\n");

    close(clientSocket);
    close(serverSocket);
    free(array);

    return 0;
}
