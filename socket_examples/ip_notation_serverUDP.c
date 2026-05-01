#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;  // Socket file descriptor for the UDP socket
    struct sockaddr_in servaddr, cliaddr;  // Server and client address structures
    char buffer[8];  // Buffer to receive the 8-byte packet
    socklen_t len = sizeof(cliaddr);  // Length of the client address structure

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create a UDP socket
    
    memset(&servaddr, 0, sizeof(servaddr));  // Zero out the server address structure
    servaddr.sin_family = AF_INET;  // IPv4 address family
    servaddr.sin_addr.s_addr = INADDR_ANY;  // Listen on all local IP interfaces
    servaddr.sin_port = htons(1025);  // Server port set to 1025, converted to network byte order

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");  // Print an error if binding the socket fails
        return 1;
    }

    // Receive the 8-byte packet from any client
    recvfrom(sockfd, buffer, 8, 0, (struct sockaddr *)&cliaddr, &len);

    // Extract data from the received packet (still in network byte order)
    uint32_t rec_ip_net;
    uint16_t rec_port_net;
    memcpy(&rec_ip_net, buffer, 4);  // First 4 bytes store the IP address
    memcpy(&rec_port_net, buffer + 5, 2);  // Bytes 5-6 store the port number

    // Display the extracted values in human-readable form
    struct in_addr ip_addr;
    ip_addr.s_addr = rec_ip_net;  // Use the network-order IP bytes directly
    uint16_t final_port = ntohs(rec_port_net);  // Convert port back to host byte order

    printf("uint32 is %u; IP is %s\n", ntohl(rec_ip_net), inet_ntoa(ip_addr));
    printf("uint16 is %u; Port is %d\n", ntohs(rec_port_net), final_port);

    close(sockfd);  // Close the UDP socket when done
    return 0;
}
