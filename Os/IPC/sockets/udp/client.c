#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int udpSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Use the same port as the server
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP

    printf("Enter a message: ");
    char message[256];
    fgets(message, sizeof(message), stdin);
    message[strlen(message) - 1] = '\0'; // Remove newline character

    // Send message to server
    if (sendto(udpSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error sending data");
        close(udpSocket);
        exit(1);
    }

    // Receive acknowledgment from server
    char buffer[256];
    int bytesRead = recvfrom(udpSocket, buffer, sizeof(buffer), 0, NULL, NULL);
    if (bytesRead == -1) {
        perror("Error receiving data");
        close(udpSocket);
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("Received acknowledgment from server: %s\n", buffer);

    // Close socket
    close(udpSocket);

    return 0;
}
