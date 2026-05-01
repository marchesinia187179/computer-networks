#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg) {
    perror(msg);  // Print the error message and the associated system error string
    exit(0);      // Exit the program with a failure code
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;  // Server address structure used for sending data
    struct hostent *server;       // DNS lookup result for the server host
    char buffer[256];             // Buffer used for both sending and receiving
    socklen_t serv_len;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);  // Convert port string to integer
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create a UDP socket
    if (sockfd < 0) error("ERROR opening socket");

    server = gethostbyname(argv[1]);  // Resolve the hostname to an IP address
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));  // Zero the server address structure
    serv_addr.sin_family = AF_INET;            // Use IPv4 addressing
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length); // Copy the resolved IP
    serv_addr.sin_port = htons(portno);        // Convert port to network byte order

    // No connect() required for UDP because sendto/recvfrom include the destination address
    printf("Please enter the message: ");
    memset(buffer, 0, 256);
    fgets(buffer, 255, stdin);  // Read a line of text from stdin

    serv_len = sizeof(serv_addr);
    // sendto instead of write: send the buffer to the UDP server address
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &serv_addr, serv_len);
    if (n < 0) error("sendto");

    memset(buffer, 0, 256);
    // recvfrom to receive a response from the server and capture the sender address
    n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *) &serv_addr, &serv_len);
    if (n < 0) error("recvfrom");

    printf("Server says: %s\n", buffer);

    close(sockfd);  // Close the UDP socket when finished
    return 0;
}
