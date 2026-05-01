#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg){
    perror(msg);  // Print the error message with the current errno description
    exit(0);      // Exit the program on error
}

int main(int argc, char *argv[]){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;  // Server address structure for connect()
    struct hostent *server;       // Result of DNS lookup for the hostname

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);  // Convert port string to integer
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket
    if (sockfd < 0) {error("ERROR opening socket");}
    server = gethostbyname(argv[1]);  // Resolve hostname to an IP address
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));  // Zero the server address structure
    serv_addr.sin_family = AF_INET;  // IPv4 family
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);  // Copy resolved IP address into serv_addr
    serv_addr.sin_port = htons(portno);  // Convert port to network byte order
    if (connect(sockfd,(const struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");  // Establish the TCP connection
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);  // Read user input from stdin
    n = write(sockfd,buffer,strlen(buffer));  // Send the message over the socket
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);  // Read the server's reply
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);  // Print the response from the server
    return 0;
}
