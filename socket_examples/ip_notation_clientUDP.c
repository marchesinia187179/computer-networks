// ./client 128.0.0.1 8080 -- sends the IP and port in a packet to the server, which then prints it out

#include <stdio.h>     // Include the standard input/output library for functions like printf, used for printing messages to the console
#include <stdlib.h>    // Include the standard library for functions like atoi (ASCII to integer conversion) and exit
#include <string.h>    // Include the string library for functions like memset and memcpy, used for memory operations
#include <unistd.h>    // Include the POSIX library for functions like close, used for closing file descriptors
#include <arpa/inet.h> // Include the ARPA internet library for network functions like inet_aton, htons, and socket operations

int main(int argc, char *argv[]) {  // Main function entry point, takes command line arguments: argc is count, argv is array of strings
    if (argc != 3) {  // Check if exactly 3 arguments are provided (program name + IP + Port), if not, print usage and exit
        printf("Usage: %s <IP> <Port>\n", argv[0]);  // Print usage message showing how to run the program with IP and Port arguments
        return 1;  // Return 1 to indicate error and exit the program
    }

    int sockfd;  // Declare an integer variable to hold the socket file descriptor
    struct sockaddr_in servaddr;  // Declare a structure to hold the server's address information (IP and port)
    char buffer[512];  // Declare a character buffer array of 512 bytes (though not used in this code, perhaps for future expansion)
    
    // Parse arguments
    char *target_ip_str = argv[1];  // Assign the second command line argument (IP address as string) to target_ip_str
    uint16_t target_port_val = (uint16_t)atoi(argv[2]);  // Convert the third argument (port as string) to unsigned 16-bit integer using atoi

    struct in_addr addr;  // Declare a structure to hold the IP address in binary form
    inet_aton(target_ip_str, &addr);  // Convert the IP address string to network byte order (big-endian) and store in addr structure
    uint32_t ip_net = addr.s_addr;  // Extract the 32-bit network-ordered IP address from the addr structure
    uint16_t port_net = htons(target_port_val);  // Convert the port number from host byte order to network byte order (big-endian) using htons

    // IP (4 bytes) + \0 (1 byte) + Port (2 bytes) + \0 (1 byte) = 8 bytes
    char packet[8];  // Declare a character array of 8 bytes to hold the packet data
    memcpy(packet, &ip_net, 4);  // Copy the 4-byte network-ordered IP address into the first 4 bytes of the packet
    packet[4] = '\0';  // Set the 5th byte to null terminator (separates IP from port in the packet)
    memcpy(packet + 5, &port_net, 2);  // Copy the 2-byte network-ordered port number into bytes 5-6 of the packet (packet + 5 points to 6th element, but since 0-indexed, it's bytes 5 and 6)
    packet[7] = '\0';  // Set the 8th byte to null terminator (ends the packet)
    
    // Info print -- must use host format
    printf("IP is %s; uint32 is %u\n", target_ip_str, ntohl(ip_net));  // Print the IP as string and its 32-bit value in host byte order (converted from network using ntohl)
    printf("Port is %d; uint16 is %u\n", target_port_val, target_port_val);  // Print the port as decimal and its 16-bit value (already in host order)

    // Send packet
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create a UDP socket (AF_INET for IPv4, SOCK_DGRAM for datagram/UDP, 0 for default protocol)
    memset(&servaddr, 0, sizeof(servaddr));  // Zero out the servaddr structure to initialize it
    servaddr.sin_family = AF_INET;  // Set the address family to IPv4
    servaddr.sin_port = htons(1025);  // Set the server's port to 1025 in network byte order (server listens on this port)
    servaddr.sin_addr.s_addr = INADDR_ANY;  // Set the server's IP to INADDR_ANY (any available interface, since it's a client sending to server)

    sendto(sockfd, packet, 8, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));  // Send the 8-byte packet to the server using sendto (UDP send function)
    
    close(sockfd);  // Close the socket file descriptor to free resources
    return 0;  // Return 0 to indicate successful execution
}
