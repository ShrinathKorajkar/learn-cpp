#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int udpSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Create socket
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Choose a port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(udpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        close(udpSocket);
        exit(1);
    }

    printf("UDP server listening...\n");

    // Receive message from client
    char buffer[256];
    int bytesRead = recvfrom(udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrSize);
    if (bytesRead == -1) {
        perror("Error receiving data");
        close(udpSocket);
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("Received message from client: %s\n", buffer);

    // Send acknowledgment to client
    const char* ack = "Message received!";
    if (sendto(udpSocket, ack, strlen(ack), 0, (struct sockaddr*)&clientAddr, addrSize) == -1) {
        perror("Error sending data");
    }

    // Close socket
    close(udpSocket);

    return 0;
}
