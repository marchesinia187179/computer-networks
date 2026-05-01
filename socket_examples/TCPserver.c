/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg){
    perror(msg);  // Print the error message and reason from errno
    exit(1);      // Exit the program on failure
}

int main(int argc, char *argv[]){
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;  // Server and client address structures
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));  // Zero the server address structure
     portno = atoi(argv[1]);  // Convert port argument from string to integer
     serv_addr.sin_family = AF_INET;  // Use IPv4
     serv_addr.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any local IP address
     serv_addr.sin_port = htons(portno);  // Convert port to network byte order
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");  // Bind the socket to the chosen port
     listen(sockfd,5);  // Listen for incoming connections, backlog of 5
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);  // Accept a single incoming connection
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);  // Read data from the connected client
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);  // Print the message received from the client
     n = write(newsockfd,"I got your message",18);  // Send a response back to the client
     if (n < 0) error("ERROR writing to socket");
     return 0; 
}
