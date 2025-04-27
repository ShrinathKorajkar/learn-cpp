#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
    <sys/socket.h>
    1. int socket(int domain, int type, int protocol);
        - address family ->  AF_INET(IPv4), AF_INET6(IPv6), AF_UNIX(AF_LOCAL), AF_BLUETOOTH, AF_NETLINK(kernel and user)
        - SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, SOCK_SEQPACKET
        - 0 for default protocol, IPPROTO_TCP, IPPROTO_UDP, IPPROTO_ICMP, IPPROTO_RAW, IPPROTO_SCTP, IPPROTO_IP
        - ret socket descriptor or -1

    2. int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        - socket descriptor ret by socket()
        - pointer to sock struct containing port, Ip addr
        - length of sock struct
        - ret 0 on success, -1 on failure

    3. int listen(int sockfd, int backlog);
        - socket descriptor of listening socket
        - max no of pending connections that can be queud for accept
        - 0 on success, -1 on failure

    4. int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        - socket descriptor of listening socket
        - pointer to struct sockaddr that will receive addr of client, can be NULL
        - pointer to len of sockaddr, NULL if not needed
        - return sock descriptor of client or -1

    5. int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        - sock descriptor of client
        - pointer to addr of server
        - len of addr
        - 0 on success, -1 on failure

    6. ssize_t send(int sockfd, const void *buf, size_t len, int flags);
       ssize_t recv(int sockfd, void *buf, size_t len, int flags);
        - socket descriptor of connected socket
        - buffer to store and receive
        - len in bytes of data
        - flags to control, usually 0, MSG_WAITALL, MSG_CONFIRM etc
        - return no of bytes received and sent, -1 otherwise

    7. int close(int sockfd);

    8. struct sockaddr - sockaddr_in, sockaddr_in6 etc

    9. ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
       ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

    10. int shutdown(int sockfd, int how);
        - SHUT_RD, SHUT_WR, SHUT_RDWR (disallow further rec, send, both)

    11. TIME_WAIT :- time for which port is unavailable for binding in TCP
*/

int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Choose a port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    int reuse = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, addrSize) == -1)
    {
        perror("Error binding socket");
        close(serverSocket);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        close(serverSocket);
        exit(1);
    }

    printf("Server listening...\n");

    // Accept client connection
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        close(serverSocket);
        exit(1);
    }

    printf("Client connected\n");

    // Receive message from client
    char buffer[256];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        close(serverSocket);
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("Received message from client: %s\n", buffer);

    // Send acknowledgment to client
    const char *ack = "Message received!";
    if (send(clientSocket, ack, strlen(ack), 0) == -1)
    {
        perror("Error sending data");
    }

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
