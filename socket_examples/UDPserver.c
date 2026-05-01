#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg) {
    perror(msg);  // Print the socket error message and errno description
    exit(1);      // Exit the program on failure
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;  // Server and client address structures

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create a UDP socket
    if (sockfd < 0) error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));  // Zero the server address structure
    portno = atoi(argv[1]);  // Convert the port argument from string to integer
    serv_addr.sin_family = AF_INET;  // Use IPv4
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // Accept datagrams on any local IP address
    serv_addr.sin_port = htons(portno);  // Convert port number to network byte order
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");  // Bind the socket to the requested port

    // No listen() or accept() in UDP because datagrams are connectionless
    clilen = sizeof(cli_addr);
    memset(buffer, 0, 256);

    // recvfrom to get data and the client's address from the incoming packet
    n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *) &cli_addr, &clilen);
    if (n < 0) error("recvfrom");

    printf("Received message: %s\n", buffer);  // Print the received client message

    // sendto to reply back to the specific client address stored in cli_addr
    n = sendto(sockfd, "I got your message", 18, 0, (struct sockaddr *) &cli_addr, clilen);
    if (n < 0) error("sendto");

    close(sockfd);  // Close the UDP socket when finished
    return 0;
}
