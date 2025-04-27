#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
    Compile the server: gcc -o server server.c -lpthread
    Compile the client: gcc -o client client.c -lpthread
    Run the server in one terminal: ./server
    Run the client in another terminal: ./client
*/

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);                  // Use the same port as the server
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error connecting to server");
        close(clientSocket);
        exit(1);
    }

    printf("Connected to server\n");

    // Send message to server
    const char *message = "Hello, server!";
    if (send(clientSocket, message, strlen(message), 0) == -1)
    {
        perror("Error sending data");
        close(clientSocket);
        exit(1);
    }

    // Receive acknowledgment from server
    char buffer[256];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        close(clientSocket);
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("Received acknowledgment from server: %s\n", buffer);

    // Close socket
    close(clientSocket);

    return 0;
}
